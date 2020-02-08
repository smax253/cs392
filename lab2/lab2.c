/*******************************************************************************
 * Name        : lab2.c
 * Author      : Max Shi
 * Date        : 2/7/2020
 * Description : Practice with pointers and strings.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define BUFLEN 128

/* Function prototypes */
size_t my_strlen(char *src);
char *my_strcpy(char *dst, char *src);

/**
 * Accepts user input from standard in, copies it to a new string, and prints
 * out the copied string and string length. You are NOT ALLOWED to use any 
 * functions from <string.h>.
 */
int main() {
    char src[BUFLEN];
    src[0] = '\0';
    char *copy;

    printf("Enter a string: ");

    if (scanf("%[^\n]", src) < 0) {
        fprintf(stderr, "Error: Failed to get a string from standard in.\n");
        return EXIT_FAILURE;
    }


    /* 1. Using malloc, allocate enough space in 'copy' to fit 'src'.
          (man 3 malloc) */
    copy = (char *) malloc((my_strlen(src)+1)*sizeof(char));
    
    my_strlen(NULL);
    if (my_strcpy(copy, NULL)) {
        fprintf(stderr, "Error: This line should not have executed!\n");
    }

    /* 2. Call my_strcpy to make a copy of src, stored in copy. */
    copy = my_strcpy(copy, src);
    /*
     * 3. Print out the following, matching the format verbatim:
     * Duplicated string: some_string
     * Length: some_length
     */
    printf("Duplicated string: %s\n", copy);
    printf("Length: %lu\n", my_strlen(copy));

    /* 
     * 4. Deallocate (free) any memory allocated with malloc/calloc/realloc/etc.
     */
    free(copy);

    return EXIT_SUCCESS;
}


/**
 * This function calculates the length of a character array passed in,
 * returning the length as a size_t. Calculation must be done via pointer
 * arithmetic. No credit will be given for calling strlen() in <string.h>.
 *
 * src: character array, possibly NULL (which will be considered length 0)
 *
 * return: length of src as a size_t
 */
size_t my_strlen(char *src) {
    if (src==NULL) return 0;
    unsigned int len = 0;
    
    while(*src){
        src++;
        len++;
    }
    return len;
}

/**
 * This function copies a character array src into dest. The caller must ensure
 * that the length of dst is at least length of src plus one. This function then
 * returns a pointer to dst. Computation must be done via pointer arithmetic.
 * No credit will be given for calling memcpy() in <string.h>.
 *
 * dst: target character array
 * src: source character array, possibly NULL
 *
 * return: pointer to dst
 *         If src is NULL, return NULL.
 */
char *my_strcpy(char *dst, char *src) {
    char* begin = dst;
    if (src==NULL) return NULL;
    while(*src){
        *begin = *src;
        begin++;
        src++;
    }
    *begin = '\0';

    return dst;
}
