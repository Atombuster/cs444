#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void){

    int file = open("foo.txt", O_CREAT|O_TRUNC|O_WRONLY, 0600);
    lseek(file, 400000000, SEEK_SET);
    write(file, "A", 1);
    close(file);
 }