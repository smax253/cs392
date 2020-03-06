#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>


#define BUFSIZE 128

int main(){
    struct dirent *de;
    DIR *dr = opendir(".");
    if (dr == NULL){
        fprintf(stderr, "Error: cannot open current directory. \n");
        exit(EXIT_FAILURE);
    }

    char buf[PATH_MAX]; /* includes \0 so +1 for null terminating is not required */
    char timebuf[BUFSIZE];
    struct stat b;
    while ((de = readdir(dr)) != NULL){
        char *res = realpath(de->d_name, buf);
        if(!res){
            fprintf(stderr, "Error: realpath() failed. %s.\n", strerror(errno));
        }
        if(!stat(buf, &b)){ //0 is success, thanks stat
            strftime(timebuf, BUFSIZE, "%b %d %Y %H:%M", localtime(&b.st_mtime));
            printf("%s [%s]\n", buf,timebuf);

        }else
            printf("%s\n", buf);
    }
    closedir(dr);
    exit(EXIT_SUCCESS);
}