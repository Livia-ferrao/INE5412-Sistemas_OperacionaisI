#ifndef FS_H
#define FS_H

#include "disk.h"
#include <vector>

class SIMPLE_FS
{
public:
    static const unsigned int FS_MAGIC = 0xf0f03410;
    static const unsigned short int INODES_POR_BLOCO = 128;
    static const unsigned short int PONTEIROS_POR_INODE = 5;
    static const unsigned short int PONTEIROS_POR_BLOCO = 1024;

    class fs_superblock {
        public:
            unsigned int magic;
            int nblocks;
            int ninodeblocks;
            int ninodes;
    }; 

    class fs_inode {
        public:
            int isvalid;
            int size;
            int direct[PONTEIROS_POR_INODE];
            int indirect;
    };

    union fs_block {
        public:
            fs_superblock super;
            fs_inode inode[INODES_POR_BLOCO];
            int pointers[PONTEIROS_POR_BLOCO];
            char data[Disk::DISK_BLOCK_SIZE];
    };

public:

    SIMPLE_FS(Disk *d) {
        disk = d;
    } 

    void fs_debug();
    int  fs_format();
    int  fs_mount();

    int  fs_create();
    int  fs_delete(int inumber);
    int  fs_getsize(int inumber);

    int  fs_read(int inumber, char *data, int length, int offset);
    int  fs_write(int inumber, const char *data, int length, int offset);

    bool load_inode(int inumber, fs_inode *node);
    vector<int> get_data_blocks(fs_inode node);

private:
    Disk *disk;
    fs_superblock MetaData;
    vector<int> inode_counter;
    vector<bool> free_blocks;
    bool mounted = false;
};

#endif