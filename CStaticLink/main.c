#include <stdio.h>
#include <stdlib.h>
#include "add.h"

#define PI 3.14159
#define E 2.71828

int main(){
    int int_result = add_ints(PI, E);
    printf("%f + %f = %d\n", PI, E, int_result);
    double double_result = add_doubles(PI, E);
    printf("%f + %f = %f\n", PI, E, double_result);
    return EXIT_SUCCESS;
}
