#include "fs.h"
#include <cstring>
#include <cmath>
#include <vector>

int INE5412_FS::fs_format()
{
	// Se o disco já foi montado retorna erro
    if(mounted){
        return 0;
    }

	// Pega bloco a ser utilizado
    union fs_block block;
    // Inicializar bloco
    //memset(&block, 0, sizeof(fs_block));

    // Armazena as informações do superbloco
    block.super.magic = INE5412_FS::FS_MAGIC;
    block.super.nblocks = (int)disk->size();
    block.super.ninodeblocks = (int)std::ceil(block.super.nblocks * 0.1);
    block.super.ninodes = block.super.ninodeblocks * INE5412_FS::INODES_PER_BLOCK;

    // Escreve informações do superbloco
    disk->write(0,block.data);

	// Percorre os blocos de inodes
    for(int i = 1; i <= block.super.ninodeblocks; i++) {
        // Pega o bloco
        union fs_block inode_block;
        // Percorre os inodes
        for(int j = 0; j < INE5412_FS::INODES_PER_BLOCK; j++) {
            // Reseta informações dos inodes
            inode_block.inode[j].size = 0;
            inode_block.inode[j].isvalid = false;
            inode_block.inode[j].indirect = 0;
            for(int t = 0; t < INE5412_FS::POINTERS_PER_INODE; t++)   
                inode_block.inode[j].direct[t] = 0;
        }
        // Escreve bloco no disco
        disk->write(i, inode_block.data);
    }

	// Reseta informações dos blocos de dados
    for(int i = block.super.ninodeblocks + 1; i < block.super.nblocks; i++) {
        // Pega bloco de dado
        union fs_block data_block;
        // Atribui 0 para os dados
        for (int j = 0; j < Disk::DISK_BLOCK_SIZE; j++) {
            data_block.data[j] = 0;
        }
        // memset(data_block.data, 0, Disk::DISK_BLOCK_SIZE);
        disk->write(i, data_block.data);
    }

	return 1;
}

void INE5412_FS::fs_debug()
{
	union fs_block block;

	disk->read(0, block.data);
    // Armazena informações do superbloco
    MetaData = block.super;

	std::cout << "superblock:\n";
	std::cout << "    " << (block.super.magic == FS_MAGIC ? "magic number is valid\n" : "magic number is invalid!\n");
 	std::cout << "    " << block.super.nblocks << " blocks\n";
	std::cout << "    " << block.super.ninodeblocks << " inode blocks\n";
	std::cout << "    " << block.super.ninodes << " inodes\n";

	// Número do inode a ser impresso na tela
    int number_inode = 0;
    // Percorre os "n" blocos de inode
    for(int i = 1; i <= MetaData.ninodeblocks; i++) {
        // Lê o bloco de inode
        disk->read(i, block.data);

        // Percorre a quantidade de inodes por bloco de inode
        for(int j = 0; j < INODES_PER_BLOCK; j++) {
            // Armazena inode em uso
            fs_inode inode_data = block.inode[j];
            // Verifica se o inode é válido
			if(inode_data.isvalid) {

                // Se for válido imprime suas informações
                std::cout << "Inode " << number_inode << ":\n";
                std::cout << "    size: " << inode_data.size << " bytes\n";
                std::cout << "    direct blocks:";

                // Percorre os ponteiros diretos do inode
                for(int t = 0; t < POINTERS_PER_INODE; t++) {
                    // Se existir o ponteiro direto imprima o número do bloco armazenado nele
                    if(inode_data.direct[t]) {
                        std::cout << " " << inode_data.direct[t];
                    }
                }
                printf("\n");

                int indirect_pointer = inode_data.indirect;
                // Verifica se existe ponteiro indireto
                if(indirect_pointer){
                    // Se existir, imprime suas informações na tela
                    std::cout << "    indirect block: " << indirect_pointer << "\n";
                    std::cout << "    indirect data blocks:";

                    // Pega o bloco indireto e percorre seus ponteiros
                    union fs_block indirect_block;
                    disk->read(indirect_pointer, indirect_block.data);

                    // Percorre os ponteiros do bloco
                    for(int t = 0; t < POINTERS_PER_BLOCK; t++) {
                        // Se existir os ponteiros imprima o número do bloco armazenado neles
                        if(indirect_block.pointers[t]) {
                            std::cout << " " << indirect_block.pointers[t];
                        }
                    }

                    std::cout << "\n";
            	}
            }
            // Soma o número do inode
            number_inode++;
        }    
    }
}


int INE5412_FS::fs_mount()
{
    // if(disk->mounted()) return false;

    //read superblock
    union fs_block block;
    disk->read(0,block.data);
    
    /**- verify valid system */
    // if(block.super.magic != FS_MAGIC) return false;
    // if(block.super.ninodeblocks != std::ceil((block.super.nblocks*1.00)/10)) return false;
    // if(block.super.ninodes != (block.super.ninodeblocks * INODES_PER_BLOCK)) return false;

    // copy metadata
    MetaData = block.super;

    // allocate free block bitmap
    free_blocks.resize(MetaData.nblocks, false);
    inode_counter.resize(MetaData.ninodeblocks, 0);
    // std::cout << "Size inode_counter: " << inode_counter.size();
    // std::cout << "Size free_blocs: " << free_blocks.size();

    // setting free bit map node 0 to true for superblock
    free_blocks[0] = true;

    //read inode blocks
    for(int i = 1; i <= MetaData.ninodeblocks; i++) {
        disk->read(i, block.data);

        for(int j = 0; j < INODES_PER_BLOCK; j++) {
            if(block.inode[j].isvalid) {
                inode_counter[i-1]++;

                // set free bit map for inode blocks
                free_blocks[i] = true;

                // set free bit map for direct pointers
                for(int k = 0; k < POINTERS_PER_INODE; k++) {
                    if(block.inode[j].direct[k]){
                        if(block.inode[j].direct[k] < MetaData.nblocks)
                            free_blocks[block.inode[j].direct[k]] = true;
                        else
                            return false;
                    }
                }

                // set free bit map for indirect pointers
                if(block.inode[j].indirect){
                    if(block.inode[j].indirect < MetaData.nblocks) {
                        free_blocks[block.inode[j].indirect] = true;
                        union fs_block indirect;
                        disk->read(block.inode[j].indirect, indirect.data);
                        for(int k = 0; k < POINTERS_PER_BLOCK; k++) {
                            if(indirect.pointers[k] < MetaData.nblocks) {
                                free_blocks[indirect.pointers[k]] = true;
                            }
                            else return false;
                        }
                    }
                    else
                        return false;
                }
            }
        }
    }

    mounted = true;

    return true;

}

int INE5412_FS::fs_create()
{
    /**- sanity check */
    if(!mounted) return false;

    /**- read the superblock */
    union fs_block block;
    disk->read(0, block.data);

    // cout << inode_counter.size();
    cout << "inode_counter: " << endl;
    for(int k = 0; k < static_cast<int>(inode_counter.size()); k++){
        cout << inode_counter[k] << " - ";
    }
    cout << endl;
    cout << "free_bloks: " << endl;
    for(int k = 0; k<static_cast<int>(free_blocks.size()); k++){
        cout << free_blocks[k] << " - ";
    }
    cout << endl;
    cout << endl;

    /**- locate free inode in inode table */    
    for(int i = 1; i <= MetaData.ninodeblocks; i++) {
        /**- check if inode block is full */
        if(inode_counter[i-1] == INODES_PER_BLOCK) continue;
        else disk->read(i, block.data);
        
        /**- find the first empty inode */
        for(int j = 0; j < INODES_PER_BLOCK; j++) {
            /**- set the inode to default values */
            if(!block.inode[j].isvalid) {
                block.inode[j].isvalid = true;
                block.inode[j].size = 0;
                block.inode[j].indirect = 0;
                for(int ii = 0; ii < 5; ii++) {
                    block.inode[j].direct[ii] = 0;
                }
                
                free_blocks[i] = true;
                inode_counter[i-1]++;

                cout << "inode_counter2: " << endl;
                for(int k = 0; k<static_cast<int>(inode_counter.size()); k++){
                    cout << inode_counter[k] << " - ";
                }
                cout << endl;
                cout << "free_bloks2: " << endl;
                for(int k = 0; k<static_cast<int>(free_blocks.size()); k++){
                    cout << free_blocks[k] << " - ";
                }
                cout << endl;

                disk->write(i, block.data);

                cout <<  "Numero inode: " << (((i-1) * INODES_PER_BLOCK) + j) << endl;

                return (((i-1) * INODES_PER_BLOCK) + j) + 1;
            }
        }
    }

	return 0;
}


bool INE5412_FS::load_inode(int inumber, fs_inode *node) {
    /** <dl class="section implementation"> */
    /** <dt> Implementation details </dt>*/
    /** </dl> */

    /**- sanity check */
    if(!mounted) return false;
    if((inumber > static_cast<int>(MetaData.ninodes)) || (inumber < 1)){return false;}

    union fs_block block;

    /**- find index of inode in the inode table */
    // Número do bloco de inode
    int i = inumber / INODES_PER_BLOCK;
    // Posição do inode
    int j = inumber % INODES_PER_BLOCK;

    // cout << "inumero: " << inumber+1 << endl;
    // cout << "i: " << i << endl;
    // cout << "j: " << j << endl;

    /**- load the inode into Inode *node */
    // Encontra o bloco que esta o inumero
    if(inode_counter[i]) {
        // Le o bloco
        disk->read(i+1, block.data);
        // Pega o inode j do bloco
        if(block.inode[j].isvalid) {
            *node = block.inode[j];
            return true;
        }
    }

    return false;
}


int INE5412_FS::fs_delete(int inumber)
{   
    /**- sanity check */
    if(!mounted) return false;

    fs_inode node;

    /**- check if the node is valid; if yes, then load the inode */
    if(load_inode(inumber-1, &node)) {
        node.isvalid = false;
        node.size = 0;

        /**- decrement the corresponding inode block in inode counter 
         * if the inode counter decreases to 0, then set the free bit map to false */ 
        if(!(--inode_counter[(inumber-1) / INODES_PER_BLOCK])) {
            free_blocks[(inumber-1) / INODES_PER_BLOCK + 1] = false;
        }

        /**- free direct blocks */
        for(int i = 0; i < POINTERS_PER_INODE; i++) {
            if(node.direct[i]) {
                free_blocks[node.direct[i]] = false;
                node.direct[i] = 0;
            }
        }

        /**- free indirect blocks */
        if(node.indirect) {
            union fs_block indirect;
            disk->read(node.indirect, indirect.data);
        
            free_blocks[node.indirect] = false;
            node.indirect = 0;

            for(int i = 0; i < POINTERS_PER_BLOCK; i++) {
                if(indirect.pointers[i]) free_blocks[indirect.pointers[i]] = false;
            }
        }

        union fs_block block;
        disk->read((inumber-1) / INODES_PER_BLOCK + 1, block.data);
        block.inode[(inumber-1) % INODES_PER_BLOCK] = node;
        disk->write((inumber-1) / INODES_PER_BLOCK + 1, block.data);

        cout << "inode_counter3: " << endl;
        for(int k = 0; k<static_cast<int>(inode_counter.size()); k++){
            cout << inode_counter[k] << " - ";
        }
        cout << endl;
        cout << "free_bloks3: " << endl;
        for(int k = 0; k<static_cast<int>(free_blocks.size()); k++){
            cout << free_blocks[k] << " - ";
        }
        cout << endl;

        return 1;
    }
    
	return 0;
}

int INE5412_FS::fs_getsize(int inumber)
{
    /**- sanity check */
    if(!mounted) return -1;

    fs_inode node;

    /**- load inode; if valid, return its size */
    if(load_inode(inumber, &node)) {
        return node.size;
    }

	return -1;
}

vector<int> INE5412_FS::get_data_blocks(fs_inode node) {
    vector<int> blocos;
    for(int i = 0; i < POINTERS_PER_INODE; i++) {
        if(node.direct[i]) {
            blocos.push_back(node.direct[i]);
        }
     }
    if(node.indirect) {
         union fs_block indirect;
         disk->read(node.indirect, indirect.data);
         for(int i = 0; i < POINTERS_PER_BLOCK; i++) {
            if(indirect.pointers[i]) {
                blocos.push_back(indirect.pointers[i]);
            }
         }
     }
    return blocos;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
    /**- sanity check */
    if(!mounted) return -1;
    fs_inode node;
    load_inode(inumber, &node);

    vector<int> blocos = get_data_blocks(node);
    int size_inode = fs_getsize(inumber);

    cout << "INUMBER: " << inumber << endl;
    cout << "LENGHT: " << length << endl;
    cout << "OFFSET: " << offset << endl;
    cout << "SIZE_INODE: " << size_inode << endl;
    cout << endl;

    for(int i = 0; i < static_cast<int>(blocos.size()); i++) {
        cout << blocos[i] << " - ";
    }
    cout << endl;

    /**- if offset is greater than size of inode, then no data can be read 
     * if length + offset exceeds the size of inode, adjust length accordingly*/
    if(offset > size_inode) {
        return 0;
    } else if(length + offset > size_inode) {
        length = size_inode - offset;
    }
    cout << "NOVO LENGHT: " << length << endl;
    
    // char *ptr = new char[Disk::DISK_BLOCK_SIZE];

    // Initialize pointers
	int startPointer = offset / Disk::DISK_BLOCK_SIZE;
	int endPointer = (offset + length) / Disk::DISK_BLOCK_SIZE;
	int blocksRead = 0;
    // Check overflow
    //bloco = node.direct(13)
    if (endPointer >= static_cast<int>(blocos.size()))
	{
		endPointer = blocos.size();
	} 

    cout << "START POINTER: " << startPointer << endl;
    cout << "END POINTER: " << endPointer << endl;
    cout << endl;

    int copy_bytes = 0;
    char* buffer = new char [(endPointer - startPointer) * Disk::DISK_BLOCK_SIZE];

    for(int i = startPointer; i < endPointer && i < static_cast<int>(blocos.size()); i++)
	{
        cout << "\n------------------NODO DIRETO:" << blocos[i] << endl;//bloco[i]
        disk->read(blocos[i], buffer);//bloco[i]
        cout << "BUFFER: " << buffer << endl;
        // *data += buffer;
        // strcat(data, buffer);
        
        strncpy(data + copy_bytes, buffer, Disk::DISK_BLOCK_SIZE);
        // memcpy(data, buffer, i * Disk::DISK_BLOCK_SIZE);

        // buffer += Disk::DISK_BLOCK_SIZE;
		// strcat(buffer, node.direct[i].data);
		blocksRead++;
        copy_bytes += Disk::DISK_BLOCK_SIZE;
	}
    
    cout << "TAMANHO buffer: "<< strlen(buffer) << endl;
    cout << "COPY BYTES: "<< copy_bytes << endl;
    cout << "TAMANHO DATA: "  << strlen(data) << endl; //20480
    //cout << "DATA: " << data << endl;
    // disk->read(node.direct[0], ptr);
    // cout << ptr << endl;
    delete [] buffer;

    // retornar blocos lidos ou que faltam pra ler?
    return copy_bytes;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{   
    //Precisa alocar mais bloco caso o tamanho passe o tamanho do inode???

    cout << endl << endl;
    cout << "INUMBER: " << inumber << endl;
    // cout << "DATA: " << data << endl;
    cout << "LENGHT: " << length << endl; //16384
    cout << "OFFSET: " << offset << endl;
    cout << "LEN DATA: " << strlen(data) << endl;

    fs_inode node;
    load_inode(inumber, &node);

    vector<int> blocos = get_data_blocks(node);
    int bytes_write = 0;
    cout << "BLOCOS.SIZE: " << blocos.size() << endl;

    int startPointer = offset / Disk::DISK_BLOCK_SIZE;
	int endPointer = (offset + length) / Disk::DISK_BLOCK_SIZE;

    if (endPointer >= static_cast<int>(blocos.size())) {
        endPointer = blocos.size();
    }
    cout << endl;
    cout << "startPointer: " << startPointer << endl;
    cout << "endPointer: " << endPointer << endl;

    for(int i = startPointer; i < endPointer && i < static_cast<int>(blocos.size()); i++){
        disk->write(blocos[i], data);

        fs_block block;
        disk->read(blocos[i], block.data);
        cout << "BLOCO[i]: " << blocos[i] << endl;
        cout << endl;
        cout << "BLOCO.DATA: " << block.data << endl;
        cout << endl;

        data += Disk::DISK_BLOCK_SIZE;
        bytes_write += Disk::DISK_BLOCK_SIZE;
	}

    node.size = max(node.size, bytes_write);

    return bytes_write;
}
