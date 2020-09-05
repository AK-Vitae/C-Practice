#include <stdio.h>

int f(int x)
{
    return 2 * x;
}

int main(int argc, char* argv[])
{
    int x = 4;
    printf("2 * %d = %d\n", x, f(x));
}