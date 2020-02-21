#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define BUFSIZE 128

bool is_integer(char *input){
    if(*input == '-' ) {
        input++;
        if(!isdigit(*input)) return false;
    }
    while(*input){
        if (!isdigit(*input)) {
            return false;
        }
        input++;
    }
    return true;
}

int get_integer(char *input, int *value){
    long long long_long_i;
    if (sscanf(input, "%lld", &long_long_i) == 1){
        *value = (int) long_long_i;
        if(long_long_i != (long long) *value){
            fprintf(stderr, "Error: Integer overflow with '%s'.\n", input);
            return false;
        }
    }
    return true;
}

int main(int argc, char * argv[]){
    if (argc != 2){
        return EXIT_FAILURE;
    }
    char buf[128];
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        puts("Error: cannot open file.");
        return EXIT_FAILURE;
    }
    while(fgets(buf, BUFSIZE, fp) != NULL){
        buf[strlen(buf)-1] = '\0';
        if (is_integer(buf)){
            int val;
            if(get_integer(buf, &val))
                printf("%d\n", val);
        }
        //printf("%s %d\n", buf, is_integer(buf));
    }
    fclose(fp);
    return EXIT_SUCCESS;
}