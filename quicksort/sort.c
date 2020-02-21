/*******************************************************************************
 * Name        : sort.c
 * Author      : Max Shi
 * Date        : 2/21/2020
 * Description : Uses quicksort to sort a file of either ints, doubles, or
 *               strings.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include "quicksort.h"

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024

typedef enum {
    STRING,
    INT,
    DOUBLE
} elem_t;

/**
 * Basic structure of sort.c:
 *
 * Parses args with getopt.
 * Opens input file for reading.
 * Allocates space in a char** for at least MAX_ELEMENTS strings to be stored,
 * where MAX_ELEMENTS is 1024.
 * Reads in the file
 * - For each line, allocates space in each index of the char** to store the
 *   line.
 * Closes the file, after reading in all the lines.
 * Calls quicksort based on type (int, double, string) supplied on the command
 * line.
 * Frees all data.
 * Ensures there are no memory leaks with valgrind.
 */
int main(int argc, char **argv) {
    int opt;
    elem_t flag = STRING;
    FILE *fp;
    char help[] =   "Usage: %s [-i|-d] [filename]\n"
                    "   -i: Specifies the file contains ints.\n"
                    "   -d: Specifies the file contains doubles.\n"
                    "   filename: The file to sort.\n"
                    "   No flags defaults to sorting strings.\n\0";
    if(argc != 2 && argc != 3) {
        printf(help, argv[0]);
        return EXIT_FAILURE;
    }
    while((opt = getopt(argc, argv, ":id")) != -1){
        switch (opt) {
            case 'i':
                flag = INT;
                break;
            case 'd':
                flag = DOUBLE;
                break;

            case '?':
                fprintf(stderr, "Unknown option '-%c' received.\n", optopt);
                printf(help, argv[0]);
                return EXIT_FAILURE;
                break;
        }
    }
    //printf("%d :: %d\n",flag, argc);
    if (argc<=optind){
        printf(help, argv[0]);
        return EXIT_FAILURE;
    }
    
    fp = fopen(argv[optind], "r");
    if (fp == NULL){
        fclose(fp);
        fprintf(stderr, "Error: cannot open file '%s'. %s.\n", argv[optind], strerror(errno));
        return EXIT_FAILURE;
    }
    int index = 0;
    char input[MAX_ELEMENTS][MAX_STRLEN+2];
    while(fgets(input[index], MAX_STRLEN+2, fp) != NULL && index<MAX_ELEMENTS){
        if(input[index][0] == '\n'){
            index--;
        }
        //printf("%ld\n", strlen(input[index]));
        input[index][strlen(input[index])-1] = '\0';
        index++;
        
    }
    //index--;
    if(flag == INT){
        //puts("sorting ints");
        int toSort[index];
        int current;
        for(int i = 0; i<index; i++){
            sscanf(input[i], "%d", &current);
            toSort[i] = current;
        }
        quicksort(&toSort, index, sizeof(int), int_cmp);
        for(int i = 0; i<index; i++){
            printf("%d\n", toSort[i]);
        }
    }
    else if (flag == DOUBLE){
        //puts("sorting doubles");
        double toSort[index];
        double current;
        for(int i = 0; i<index; i++){
            sscanf(input[i], "%lf", &current);
            toSort[i] = current;
        }
        quicksort(&toSort, index, sizeof(double), dbl_cmp);
        for(int i = 0; i<index; i++){
            printf("%f\n", toSort[i]);
        }
    }
    else{
        char toSort[index][MAX_STRLEN+2];
        for(int i = 0; i<index; i++){
            strcpy(toSort[i], input[i]);
        }
        quicksort(&toSort, index, MAX_STRLEN+2, str_cmp);
        for(int i = 0; i<index; i++){
            printf("%s\n", toSort[i]);
        }
    }
    fclose(fp);

    return EXIT_SUCCESS;
}
