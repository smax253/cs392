#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

void print_str(void *str) {
    printf("\"%s\"", (char *)str);
}

int str_cmp(const void *a, const void *b) { 
    return strcmp((const char*)a, (const char*)b);
}

void insert_word(linked_list *list, char *word) {
    insert_in_order(list, create_node((void *)strdup(word)), str_cmp);
}

int main() {
    linked_list *list = create_linked_list();
    print_list(list, print_str);

    insert_word(list, "hello");
    print_list(list, print_str);

    insert_word(list, "max");
    print_list(list, print_str);

    insert_word(list, "borowski");
    print_list(list, print_str);

    insert_word(list, "abacadabra");
    print_list(list, print_str);

    insert_word(list, "zlooool");
    print_list(list, print_str);

    free_list(list, free);
    free(list);
    puts("If you can read this message, your program exited successfully.");

    return 0;
}
