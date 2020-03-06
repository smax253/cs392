#include <stdio.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

#define PI 3.14159
#define E 2.71828

int main(){
    printf("Hello world!\n");
    printf("%f\n", MAX(PI, E));
    return 0;
}