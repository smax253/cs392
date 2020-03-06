/*******************************************************************************
 * Name        : permstat.c
 * Author      : Max Shi and Hamzah Nizami
 * Date        : 2/26/2020
 * Description : Print out the file permissions of a given file.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int perms[] = {S_IRUSR, S_IWUSR, S_IXUSR,
               S_IRGRP, S_IWGRP, S_IXGRP,
               S_IROTH, S_IWOTH, S_IXOTH};

void display_usage(char *progname) {
    printf("Usage: %s <filename>\n", progname);
}

/**
 * TODO
 * Returns a string (pointer to char array) containing the permissions of the
 * file referenced in statbuf.
 * Allocates enough space on the heap to hold the 10 printable characters.
 * The first char is always a - (dash), since all files must be regular files.
 * The remaining 9 characters represent the permissions of user (owner), group,
 * and others: r, w, x, or -.
 */
char* permission_string(struct stat *statbuf) {
    char* result = (char*) malloc(11*sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Failed to malloc.\n");
        exit(EXIT_FAILURE);
    }
    char* current = result;
    *current = '-';
    current++;
    int permission_valid;
    for(int i = 0; i<9; i+=3){
        permission_valid = statbuf->st_mode & perms[i];
        if(permission_valid){
            *current = 'r';
        }
        else {
            *current = '-';
        }
        current++;
        permission_valid = statbuf->st_mode & perms[i+1];
        if(permission_valid){
            *current = 'w';
        }
        else {
            *current = '-';
        }
        current++;
        permission_valid = statbuf->st_mode & perms[i+2];
        if(permission_valid){
            *current = 'x';
        }
        else {
            *current = '-';
        }
        current++;
    }
    *current = '\0';
    return result;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        display_usage(argv[0]);
        return EXIT_FAILURE;
    }

    struct stat statbuf;
    if (stat(argv[1], &statbuf) < 0) {
        fprintf(stderr, "Error: Cannot stat '%s'. %s.\n", argv[1],
                strerror(errno));
        return EXIT_FAILURE;
    }

    /* TODO
     * If the argument supplied to this program is not a regular file,
     * print out an error message to standard error and return EXIT_FAILURE.
     * For example:
     * $ ./permstat iamdir
     * Error: 'iamdir' is not a regular file.
     */
    if (!S_ISREG(statbuf.st_mode)){
        fprintf(stderr, "Error: '%s' is not a regular file.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    char *perms = permission_string(&statbuf);
    printf("Permissions: %s\n", perms);
    free(perms);

    return EXIT_SUCCESS;
}
