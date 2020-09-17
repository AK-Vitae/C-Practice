// Basic implementation of pointers

#include <stdio.h>

int main(void)
{
    int a;
    int *p;
    a = 10;
    p = &a; // &a = address of a
    printf("%d\n", p);
    printf("%d\n", *p); // *p- value at address pointed by p
    printf("%d\n", &a); // prints out the address of a
    printf("\n");
    printf("a = %d\n", a);
    *p = 12; // dereferencing
    printf("a = %d\n", a);
    printf("\n");
    int b = 20;
    *p = b;
    printf("%d\n", p);
    printf("b = %d\n", b);
    printf("*p = %d\n", *p);
    printf("a = %d\n", a); //Put the value of b into a but does not change the address
    printf("%d\n", p);
}