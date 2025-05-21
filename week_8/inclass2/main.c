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
    // TODO
    DIR *opendir(const char *name);
    while (int something != NUll) {
    something = *readdir(DIR *dirp);
    printf("%d%c\n", something->d_ino, something->d_ino);
    stat(name, something->d_ino);
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
