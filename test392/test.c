#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y) (((x)<(y)) ? (x) : (y))

typedef union my_union {
    char c;
    short s;
    int i;
} my_union_t;

void display (my_union_t u) {
    printf("%c\n", u.c);
    printf("%d\n", u.s);
    printf("%d\n", u.i);
}

void display_bits(my_union_t u){
    unsigned int p,
        num_bytes = MIN(sizeof(my_union_t), sizeof(unsigned int));
    memcpy(&p, &u, num_bytes);
    putchar('|');
    for (int i = num_bytes * 8 - 1, mask = 1 << i; i >= 0; i--){
        if (p & mask) {
            putchar('1');
        }else{
            putchar('0');
        }
        if (i % 8 == 0){
            putchar('|');
        }
        mask >>= 1;
    }
    putchar('\n');
}

int main(int argc, char **argv) {
    my_union_t u;
    int var0;
    u.i = 0;
    display(u);
    u.c = 'A';
    display(u);
    u.s = 16383;
    display(u);

    var0 = u.c;
    printf("%d\n", u.c);
    printf("%d\n", var0);
    display_bits(u);
    return 0;
}
