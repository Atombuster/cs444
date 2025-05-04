#define BLOCK_SIZE 4096
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "image.h"

unsigned char *bread(int block_num, unsigned char *block){
    
    off_t offset = block_num * BLOCK_SIZE;

    lseek(image_fd, offset, SEEK_SET); 

    read(image_fd, block, BLOCK_SIZE);

    return block;
}

void bwrite(int block_num, unsigned char *block){

    off_t offset = block_num * BLOCK_SIZE;

    lseek(image_fd, offset, SEEK_SET); 

    write(image_fd, block, BLOCK_SIZE);

}