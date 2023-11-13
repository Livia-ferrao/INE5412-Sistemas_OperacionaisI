#include "fs.h"
#include <cstring>
#include <cmath>

int INE5412_FS::fs_format()
{
	// Como sei que o disco já foi montado?
	// if(disk->mounted()) return false;

	/**- write superblock */
    union fs_block block;
    memset(&block, 0, sizeof(fs_block));

    block.super.magic = INE5412_FS::FS_MAGIC;
    block.super.nblocks = (uint32_t)(disk->size());
    block.super.ninodeblocks = (uint32_t)std::ceil(block.super.nblocks * 0.1);
    block.super.ninodes = block.super.ninodeblocks * (INE5412_FS::INODES_PER_BLOCK);

    disk->write(0,block.data);

	/**- clear all other blocks (inodes) */
    for(uint32_t i = 1; i <= block.super.ninodeblocks; i++){
        union fs_block inodeblock;

        /**- clear individual Inodes */
        for(uint32_t j = 0; j < INE5412_FS::INODES_PER_BLOCK; j++){
            inodeblock.inode[j].isvalid = false;
            inodeblock.inode[j].size = 0;

            /**- clear all direct Pointers */
            for(uint32_t k = 0; k < INE5412_FS::POINTERS_PER_INODE; k++)   
                inodeblock.inode[j].direct[k] = 0;
    
            /**- clear indirect Pointer */
            inodeblock.inode[j].indirect = 0;
        }

        disk->write(i,inodeblock.data);
    }

	/**- Free Data Blocks */
    for(uint32_t i = (block.super.ninodeblocks) + 1; i < block.super.nblocks; i++) {
        union fs_block datablock;
        memset(datablock.data, 0, Disk::DISK_BLOCK_SIZE);
        disk->write(i, datablock.data);
    }

	return 1;
}

void INE5412_FS::fs_debug()
{
	union fs_block block;


	disk->read(0, block.data);
    MetaData = block.super; 

	cout << "superblock:\n";
	cout << "    " << (block.super.magic == FS_MAGIC ? "magic number is valid\n" : "magic number is invalid!\n");
 	cout << "    " << block.super.nblocks << " blocks\n";
	cout << "    " << block.super.ninodeblocks << " inode blocks\n";
	cout << "    " << block.super.ninodes << " inodes\n";

	/**- reading the inode blocks */
    int ii = 0;
    for(uint32_t i = 1; i <= MetaData.ninodeblocks; i++) { // passa pelos 3 blocos de inodes (de 20)
        printf("BLOCK %u:\n", i);
        disk->read(i, block.data); /**-  array of inodes */
        for(uint32_t j = 0; j < INODES_PER_BLOCK; j++) {   // cada um dos 3 tem 128 inodos (128*3=384)
            /**- iterating through INODES_PER_BLOCK inodes */
			if(block.inode[j].isvalid) {
				printf("Inode %u:\n", ii);
				printf("    size: %u bytes\n", block.inode[j].size);
				printf("    direct blocks:");

                /** iterating through the direct nodes */
                for(uint32_t k = 0; k < POINTERS_PER_INODE; k++) {
                    if(block.inode[j].direct[k]) printf(" %u", block.inode[j].direct[k]);
                }
                printf("\n");

                /**- iterate through the indirect nodes */
                if(block.inode[j].indirect){
                    printf("    indirect block: %u\n    indirect data blocks:",block.inode[j].indirect);
                    union fs_block indirectblock;
                    disk->read(block.inode[j].indirect, indirectblock.data);
                    for(uint32_t k = 0; k < POINTERS_PER_BLOCK; k++) {
                        if(indirectblock.pointers[k]) printf(" %u", indirectblock.pointers[k]);
                    }
                    printf("\n");
            	}
            }

            ii++;
        }    
    }
}

int INE5412_FS::fs_mount()
{
	/**- sanity check */
    // if(disk->mounted()) return false;

    /**- read superblock */
    union fs_block block;
    disk->read(0,block.data);
    
    /**- verify valid system */
    if(block.super.magic != FS_MAGIC) return false;
    if(block.super.ninodeblocks != std::ceil((block.super.nblocks*1.00)/10)) return false;
    if(block.super.ninodes != (block.super.ninodeblocks * INODES_PER_BLOCK)) return false;

    /**- copy metadata */
    MetaData = block.super; 

    /**- allocate free block bitmap */ 
    free_blocks.resize(MetaData.nblocks, false);

    /**- allocate inode counter */
    inode_counter.resize(MetaData.ninodeblocks, 0);

    // size_t sizeInBytes = sizeof(inode_counter[0]);
    // size_t sizeInBytes = sizeof(inode_counter[1]);

    // std::cout << "Tamanho do inode_counter em bytes: " << sizeInBytes << std::endl;

    /**- setting free bit map node 0 to true for superblock */
    free_blocks[0] = true;

     /**- read inode blocks */
    for(uint32_t i = 1; i <= MetaData.ninodeblocks; i++) {
        disk->read(i, block.data);

        for(uint32_t j = 0; j < INODES_PER_BLOCK; j++) {
            if(block.inode[j].isvalid) {
                inode_counter[i-1]++;

                /**- set free bit map for inode blocks */
                free_blocks[i] = true;

                /**- set free bit map for direct pointers */
                for(uint32_t k = 0; k < POINTERS_PER_INODE; k++) {
                    if(block.inode[j].direct[k]){
                        if(block.inode[j].direct[k] < MetaData.nblocks)
                            free_blocks[block.inode[j].direct[k]] = true;
                        else
                            return false;
                    }
                }

                /**- set free bit map for indirect pointers */
                if(block.inode[j].indirect){
                    if(block.inode[j].indirect < MetaData.nblocks) {
                        free_blocks[block.inode[j].indirect] = true;
                        union fs_block indirect;
                        disk->read(block.inode[j].indirect, indirect.data);
                        for(uint32_t k = 0; k < POINTERS_PER_BLOCK; k++) {
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
    // for(int k; k<free_blocks.size(); k++){
    //     cout << free_blocks[k] << " - ";
    // }
    // inode_counter[0] = 2;
    // inode_counter[1] = 3;
    // // Antes de acessar os elementos do vetor
    // if (!inode_counter.empty()) {
    //     cout << inode_counter[0];
    //     cout << inode_counter[1];
    // } else {
    //     cout << "Error: inode_counter is empty." << endl;
    // }

    cout << inode_counter.size() << endl;
    for(int k = 0; k<inode_counter.size(); k++){
        cout << k << endl;
        cout << inode_counter[k] << endl;
    }
    

    return true;

	// return 0;
}

int INE5412_FS::fs_create()
{
    /**- sanity check */
    // if(!mounted) return false;

    /**- read the superblock */
    union fs_block block;
    disk->read(0, block.data);

    cout << inode_counter.size();
    for(int k; k<inode_counter.size(); k++){
        cout << inode_counter[k];
    }

    /**- locate free inode in inode table */    
    for(uint32_t i = 1; i <= MetaData.ninodeblocks; i++) {
        cout << "entrou aqui2" << endl;
        /**- check if inode block is full */
        if(inode_counter[i-1] == INODES_PER_BLOCK) continue;
        else disk->read(i, block.data);
        
        cout << "entrou aqui3" << endl;
        /**- find the first empty inode */
        for(uint32_t j = 0; j < INODES_PER_BLOCK; j++) {
            cout << "entrou aqui4" << endl;
            /**- set the inode to default values */
            if(!block.inode[j].isvalid) {
                block.inode[j].isvalid = true;
                block.inode[j].size = 0;
                block.inode[j].indirect = 0;
                for(int ii = 0; ii < 5; ii++) {
                    block.inode[j].direct[ii] = 0;
                }
                for(int k; k<free_blocks.size(); k++){
                    cout << free_blocks[k];
                }
                
                free_blocks[i] = true;
                inode_counter[i-1]++;

                disk->write(i, block.data);
                cout << "entrou aqui5" << endl;

                return (((i-1) * INODES_PER_BLOCK) + j);
            }
        }
    }

	return 0;
}

int INE5412_FS::fs_delete(int inumber)
{
	return 0;
}

int INE5412_FS::fs_getsize(int inumber)
{
	return -1;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
	return 0;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{
	return 0;
}
