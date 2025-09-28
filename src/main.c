#include "example.h"
#include <stdio.h>

int main(void) {
    printf("%s\n", get_greeting());

    int a = 5, b = 3;
    printf("Adding %d + %d = %d\n", a, b, add(a, b));
    printf("Multiplying %d * %d = %d\n", a, b, multiply(a, b));

    return 0;
}