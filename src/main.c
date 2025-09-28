#include <stdio.h>

#include "example.h"

int main()
{
    int a = 5, b = 3;

    printf("C Project Template Example\n");
    printf("=========================\n");
    printf("a = %d, b = %d\n", a, b);
    printf("add(%d, %d) = %d\n", a, b, add(a, b));
    printf("multiply(%d, %d) = %d\n", a, b, multiply(a, b));
    printf("is_even(%d) = %s\n", a, is_even(a) ? "true" : "false");
    printf("is_even(%d) = %s\n", b, is_even(b) ? "true" : "false");

    return 0;
}