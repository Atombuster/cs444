#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

/*
 * Takes a dirname as a string ("." for current directory) and shows the
 * contents of that directory.
 */
void ls(const char *dirname)
{
    char fullpath[4096];
    struct dirent *something;
    DIR *file = opendir(dirname);
    struct stat statbuf;
    while ((something = readdir(file)) != NULL) {
        printf("Part 1: Inode number = %ld, Filename = %s\n\n", something->d_ino, something->d_name);
        sprintf(fullpath, "%s/%s",dirname, something->d_name);
        stat(fullpath, &statbuf);
        //printf("%s\n", fullpath);
        printf("Part 2: Filename = %s,\n Inode number = %ld,\n Octal = %o,\n User = %d,\n Group = %d,\n Size = %ld,\n Block Size = %ld,\n The number of 512-byte blocks allocated = %ld\n\n", something->d_name, something->d_ino, statbuf.st_mode, statbuf.st_uid, statbuf.st_gid, statbuf.st_size, statbuf.st_blksize, statbuf.st_blocks);
    }
    int closedir(DIR *dirp);
    

}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: myls dirname\n");
        exit(1);
    }

    char *dirname = argv[1];
    
    ls(dirname);
}
