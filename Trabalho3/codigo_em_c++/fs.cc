#include "fs.h"
#include <cstring>
#include <cmath>
#include <vector>

int INE5412_FS::fs_format()
{
	// Se o disco já foi montado retorna erro
    if(!mounted) {
        // Pega bloco a ser utilizado
        union fs_block block;
    
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
                // Reseta ponteiros diretos
                for(int t = 0; t < INE5412_FS::POINTERS_PER_INODE; t++) {
                    inode_block.inode[j].direct[t] = 0;
                }

                // Reseta ponteiro indireto
                inode_block.inode[j].indirect = 0;
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
        
    } else {
        // Erro
        return 0;
    }

	return 1;
}

void INE5412_FS::fs_debug()
{
	union fs_block block;

	disk->read(0, block.data);
    // Armazena informações do superbloco
    context = block.super;

	std::cout << "superblock:\n";
	std::cout << "    " << (block.super.magic == FS_MAGIC ? "magic number is valid\n" : "magic number is invalid!\n");
 	std::cout << "    " << block.super.nblocks << " blocks\n";
	std::cout << "    " << block.super.ninodeblocks << " inode blocks\n";
	std::cout << "    " << block.super.ninodes << " inodes\n";

	// Número do inode a ser impresso na tela
    int number_inode = 1;
    // Percorre os "n" blocos de inode
    for(int i = 1; i <= context.ninodeblocks; i++) {
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
    // Verifica se o disco ainda não foi montado
    if(!mounted){
        // Lê o superbloco
        union fs_block block;
        disk->read(0,block.data);

        // Armazena informações do superbloco
        context = block.super;

        // Inicializa como false o bitmap
        for (int i = 0; i < context.nblocks; ++i) {
            bitmap.push_back(false);
        }
        // Bitmap 0 que é o superbloco recebe Verdadeiro pois está ocupado
        bitmap[0] = true;

        // Inicializa como 0 a contagem de inodes
        for (int i = 0; i < static_cast<int>(context.ninodeblocks); ++i) {
            counter_inode.push_back(0); 
        }
        
        //Interação para preencher o bitmap
        for(int i = 1; i <= context.ninodeblocks; i++) {
            // Le os blocos de inode
            disk->read(i, block.data);
            // Percorre os inodes
            for(int j = 0; j < INODES_PER_BLOCK; j++) {

                // Entra se inode for válido
                if(block.inode[j].isvalid) {
                    // Incrementa um na contagem de inodes
                    counter_inode[i-1] += 1;

                    // Coloca bitmap para Verdadeiro
                    bitmap[i] = true;

                    // Percorre ponteiros diretos
                    for(int k = 0; k < POINTERS_PER_INODE; k++) {
                        // Entra se existir o ponteiro direto
                        if(block.inode[j].direct[k]){
                            // Pega bloco direto
                            int direct_block = block.inode[j].direct[k];
                            // Seta para Verdadeiro o bloco direto
                            bitmap[direct_block] = true;
                        }
                    }

                    // Verifica se existe ponteiro indireto
                    if(block.inode[j].indirect){
                        // Pega número do bloco indireto
                        int indirect_block = block.inode[j].indirect;
                        // Coloca como Verdadeiro no bitmap
                        bitmap[indirect_block] = true;

                        // Pega bloco indireto
                        union fs_block indirect;
                        // Le bloco indireto
                        disk->read(block.inode[j].indirect, indirect.data);
                        // Percorre cada ponteiro indireto
                        for(int k = 0; k < POINTERS_PER_BLOCK; k++) {
                            // Pega número do bloco do ponteiro indireto
                            int indirect_pointer = indirect.pointers[k];
                            // Coloca como Verdadeiro no bitmap
                            bitmap[indirect_pointer] = true;  
                        }
                        
                    }
                }
            }
        }

        // Está montado
        mounted = true;
        // Retorna verdadeiro
        return true;
    } else {
        return false;
    }
}

int INE5412_FS::fs_create()
{
    // Verifica se o disco já foi montado
    if(mounted) {
        // Lê o superbloco
        union fs_block block;
        disk->read(0, block.data);

        // Percorre blocos de inode
        for(int i = 1; i <= context.ninodeblocks; i++) {
            // Verifica se o bloco de inode está cheio (Para estar cheio tem que ser igual 128)
            if(counter_inode[i-1] == INODES_PER_BLOCK) { 
                // Volta para o for e pega próximo bloco de inode
                continue;
            } else {
                // Se não estiver cheio, lê o bloco de inode
                disk->read(i, block.data);
            }
            
            // Percorre os inodes
            for(int j = 0; j < INODES_PER_BLOCK; j++) {
                // Encontra primeiro inode não válido para ser criado
                if(!block.inode[j].isvalid) {
                    // Seta tamanho para 0
                    block.inode[j].size = 0;
                    // Seta ele como válido
                    block.inode[j].isvalid = true;
                    // Seta ponteiros diretos como 0
                    for(int ii = 0; ii < 5; ii++) {
                        block.inode[j].direct[ii] = 0;
                    }
                    // Seta ponteiro indireto como 0
                    block.inode[j].indirect = 0;

                    // Bloco em que esse inode é criado é colcoado como Verdadeiro
                    bitmap[i] = true;
                    // Incrementa número de inodes no bloco
                    counter_inode[i-1] += 1;

                    // Escreve bloco no disco
                    disk->write(i, block.data);

                    // Calcula o número do inode criado
                    int num_inode = (((i-1) * INODES_PER_BLOCK) + j) + 1;
                    // Retorna esse número
                    return num_inode;
                }
            }
        }

        return 0;

    } else {
        return 0;
    }
}


bool INE5412_FS::load_inode(int inumber, fs_inode *node) {

    // Pega bloco
    union fs_block block;
    
    // Posição do inode no bloco
    int position = inumber % INODES_PER_BLOCK;

    // Encontra bloco do inode e lê o bloco
    disk->read((inumber / INODES_PER_BLOCK) + 1, block.data);
    // Verifica se o inode na posição é valido
    if(block.inode[position].isvalid) {
        // Seta o ponteiro para o inode
        *node = block.inode[position];
        // Operação realizada com sucesso
        return true;
    }

    return false;
}


int INE5412_FS::fs_delete(int inumber)
{   
    // Verifica se está montado
    if(mounted) {
        // Pega inode
        fs_inode node;

        // Carrega o inode
        if(load_inode(inumber-1, &node)) {
            // Reseta inode
            node.isvalid = false;
            node.size = 0;

            // Pega o bloco de inode que o inumber está
            int inode_block = (inumber-1) / INODES_PER_BLOCK;

            if(!(--counter_inode[inode_block])) {
                // Caso o contador de inodes chegue em 0, o bitmap precisa ser liberado
                bitmap[inode_block + 1] = false;
            }

            // Percorre ponteiros diretos
            for(int i = 0; i < POINTERS_PER_INODE; i++) {
                // Entra se o ponteiro existir
                if(node.direct[i]) {
                    // Pega os blocos diretos
                    int direct_block = node.direct[i];
                    // Libera bloco
                    bitmap[direct_block] = false;
                    // Ponteiro direto é resetado
                    node.direct[i] = 0;
                }
            }

            // Verifica se ponteiro indireto existe
            if(node.indirect) {
                // Bloco indireto
                union fs_block indirect;
                // Lê o bloco indireto
                disk->read(node.indirect, indirect.data);
                // Libera bitmap para este bloco
                bitmap[node.indirect] = false;
                // Ponteiro indireto resetado
                node.indirect = 0;
                // Percorre ponteiros indiretos
                for(int i = 0; i < POINTERS_PER_BLOCK; i++) {
                    // Entra se existir ponteiro indireto
                    if(indirect.pointers[i]) {
                        // Libera blocos desses ponteiros indiretos
                        bitmap[indirect.pointers[i]] = false;
                    }
                }
            }

            // Pega bloco
            union fs_block block;
            // Pega o bloco de inode que o inumber está
            int inode_block_number = (inumber-1) / INODES_PER_BLOCK + 1;
            // Lê bloco em que inode pertence
            disk->read(inode_block_number, block.data);
            // Bloco recebe o inode modificado
            block.inode[(inumber-1) % INODES_PER_BLOCK] = node;
            // Escreve no disco o bloco
            disk->write(inode_block_number, block.data);

            return 1;
        }
        
        return 0;

    } else {
        return 0;
    }

}

int INE5412_FS::fs_getsize(int inumber)
{
    // Pega inode
    fs_inode node;

    /// Carrega inode e retorna tamanho
    if(load_inode(inumber, &node)) {
        return node.size;
    }

	return -1;
}

vector<int> INE5412_FS::get_data_blocks(fs_inode node) {
    // Vetor de blocos
    vector<int> blocks;
    // Percorre ponteiros diretos
    for(int i = 0; i < POINTERS_PER_INODE; i++) {
        // Verifica se existe ponteiro direto
        if(node.direct[i]) {
            // Se existir, coloca no vetor o bloco direto
            blocks.push_back(node.direct[i]);
        }
     }
    // Verifica existencia de bloco indireto
    if(node.indirect) {
        // Pega bloco indireto
        union fs_block indirect;
        // Lê bloco indireto
        disk->read(node.indirect, indirect.data);
        // Percorre ponteiros do bloco indireto
        for(int i = 0; i < POINTERS_PER_BLOCK; i++) {
            // Verifica se existem pblocos nos ponteiros indiretos
            if(indirect.pointers[i]) {
                // Se existir, coloca no vetor os blocos
                blocks.push_back(indirect.pointers[i]);
            }
        }
     }
    
    // Retorna vetor de blocos
    return blocks;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
    // Verifica se o disco está montado
    if(mounted) {
        // Pega o inode
        fs_inode node;
        // Carrega o inode pelo inumber
        load_inode(inumber, &node);
        // Pega os blocos diretos e indiretos
        vector<int> blocks = get_data_blocks(node);
        // Tamanho do inode
        int size_inode = fs_getsize(inumber);

        // Se o offset for maior que o tamanho do inode retorna erro
        if(offset > size_inode) {
            return 0;
        // Entra se o tamanho mais o offset for maior que o tamanho do inode
        } else if(length + offset > size_inode) {
            // Ajusta o tamanho de acordo com o máximo que ele pode assumir
            length = size_inode - offset;
        }
        // cout << "NOVO LENGHT: " << length << endl;
        
        // Primeiro bloco de leitura
        int startPointer = offset / Disk::DISK_BLOCK_SIZE;
        // Último bloco de leitura
        int endPointer = (offset + length) / Disk::DISK_BLOCK_SIZE;
        
        // Se o último bloco for maior do que o permitido, endPointer recebe o último bloco
        if (endPointer >= static_cast<int>(blocks.size()))
        {   
            // endPointer recebe o último bloco
            endPointer = blocks.size();
        } 

        // Bytes lidos do inodo 
        int copy_bytes = 0;
        // Buffer para armazenar o texto lido
        char* buffer = new char [(endPointer - startPointer) * Disk::DISK_BLOCK_SIZE];

        // Percorre os blocos do disco
        for(int i = startPointer; i < endPointer && i < static_cast<int>(blocks.size()); i++)
        {   
            // Lê o bloco de dados e coloca para o buffer
            disk->read(blocks[i], buffer);
            // Concatena os dados do buffer com data
            strncpy(data + copy_bytes, buffer, Disk::DISK_BLOCK_SIZE);
            // 1 bloco lido, então incrementa-se valor do bloco
            copy_bytes += Disk::DISK_BLOCK_SIZE;
        }

        
        // Deleta buffer
        delete [] buffer;

        // Retorna quantidade de bytes lidos
        return copy_bytes;
    } else {
        return -1;
    }    
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{   
    // Verifica se o disco está montado    
    if(mounted) {
        // Pega o inode
        fs_inode node;
        // Carrega o inode pelo inumber
        load_inode(inumber, &node);
        // Pega os blocos diretos e indiretos
        vector<int> blocos = get_data_blocks(node);
        // Configura os bytes escritos para 0
        int bytes_write = 0;
        
        // Configura ponteiros de inicio que serão utilizados no bloco
        int startPointer = offset / Disk::DISK_BLOCK_SIZE;
        // Configura ponteiros de fim que serão utilizados no bloco
        int endPointer = (offset + length) / Disk::DISK_BLOCK_SIZE;

        // Verifica se não há overflow
        if (endPointer >= static_cast<int>(blocos.size())) {
            endPointer = blocos.size();
        }
        
        // Percorre cada bloco para fazer a ecrita
        for(int i = startPointer; i < endPointer && i < static_cast<int>(blocos.size()); i++){
            // Faz a escrita do data no bloco
            disk->write(blocos[i], data);
            
            // Incrementa o tamanho do bloco no dado para que a próxima leitura se inicie no ponto certo
            data += Disk::DISK_BLOCK_SIZE;
            // Seta os valores de bytes escritos
            bytes_write += Disk::DISK_BLOCK_SIZE;
        }

        // Ajusta tamanho do inode utilizado
        node.size = max(node.size, bytes_write);

        // Retorna quantidade de bytes escritos
        return bytes_write;
    } else {
        return -1;
    }
    
}
