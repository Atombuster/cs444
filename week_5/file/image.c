#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "image.h"

int image_fd;

int image_open(char *filename, int truncate){
    int flag = O_RDWR|O_CREAT;
    if(truncate){
        flag |= O_TRUNC;
    }
    image_fd = open(filename, flag, 0600);

    return image_fd;
}


int image_close(void){
    return close(image_fd);
}