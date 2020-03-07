#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

#define match_perms(a,b) (((a)&(b))==(a))

int perms[] = {S_IRUSR, S_IWUSR, S_IXUSR,
               S_IRGRP, S_IWGRP, S_IXGRP,
               S_IROTH, S_IWOTH, S_IXOTH};

void display_usage(char *filepath){
    char help_str[] = "Usage: %s -d <directory> -p <permissions string> [-h]\n";
    printf(help_str, filepath);
}

int permstring_to_int(char *permstring){
    if (strlen(permstring)!=9) return -1;
    int result = 0;
    for(int i = 0; i<9; i+=3){
        if(permstring[i] != '-' && permstring[i] != 'r') return -1;
        else if(permstring[i] == 'r') result = result | perms[i];
        
        if(permstring[i+1] != '-' && permstring[i+1] != 'w') return -1;
        else if(permstring[i+1] == 'w') result = result | perms[i+1];
        
        if(permstring[i+2] != '-' && permstring[i+2] != 'x') return -1;
        else if(permstring[i+2] == 'x') result = result | perms[i+2];
    }
    return result;
}

void navigate(int permval, char *dir_path){
    DIR *dir;
    if((dir = opendir(dir_path))==NULL){
        fprintf(stderr, "Error: Cannot open directory '%s'. %s\n", dir_path, strerror(errno));
        return;
    }
    struct dirent *entry;
    struct stat sb;
    char full_filename[PATH_MAX];
    size_t pathlen = 0;

    full_filename[0] = '\0';
    if (strcmp(dir_path, "/")){
        //if path is not root
        strncpy(full_filename, dir_path, PATH_MAX-1);
    }
    pathlen = strlen(full_filename)+1; //add 1 because we're going to add a '/'.

    full_filename[pathlen-1] = '/';
    full_filename[pathlen] = '\0';

    while((entry = readdir(dir))!=NULL){
        if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0){
            continue;
        }
        strncpy(full_filename+pathlen, entry->d_name, PATH_MAX-pathlen);
        if (lstat(full_filename, &sb)<0){
            fprintf(stderr, "Error: Cannot stat file '%s'. %s\n", full_filename, strerror(errno));
            continue;
        }
        if(entry->d_type == DT_DIR){
            if(match_perms(permval, sb.st_mode)){
                printf("%s\n", full_filename);
                
            }
            navigate(permval, full_filename);
        }
        else{
            if(match_perms(permval, sb.st_mode)){
                printf("%s\n", full_filename);
            }
        }
    }
    closedir(dir);
}

int main(int argc, char * argv[]){
    int opt;
    char *perm_string, *dir_path;
    bool pflag = false, dflag = false;
    if(argc == 1){
        display_usage(argv[0]);
        return EXIT_FAILURE;
    }
    while((opt = getopt(argc, argv, ":d:p:h")) != -1){//d - directory, p- perm string
        switch (opt) {
            case 'p':
                perm_string = optarg;
                pflag = true;
                break;
            case 'd':
                dir_path = optarg;
                dflag = true;
                break;
            case 'h':
                display_usage(argv[0]);
                return EXIT_SUCCESS;
            case '?':
                fprintf(stderr, "Unknown option '-%c' received.\n", optopt);
                return EXIT_FAILURE;
                break;
        }
    }
    if(!dflag){
        fprintf(stderr, "Error: Required argument -d <directory> not found.\n");
        return EXIT_FAILURE;
    }
    else if(!pflag){
        fprintf(stderr, "Error: Required argument -p <permissions string> not found.\n");
        return EXIT_FAILURE;
    }
    int perm_code = permstring_to_int(perm_string);
    //printf("Perm string: %s, Dir path: %s, Perm Code: %d\n", perm_string, dir_path, perm_code);
    
    char path[PATH_MAX];
    if(realpath(dir_path, path) == NULL){
        fprintf(stderr, "Error: Cannot get full path of file '%s'. %s.\n", dir_path, strerror(errno));
        return EXIT_FAILURE;
    }
    navigate(perm_code, path);
    return EXIT_SUCCESS;
}
