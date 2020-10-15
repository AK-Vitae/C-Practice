#include <stdio.h>
#include <stdlib.h>

// Driver
int main(int argc, char *argv[])
{
    // Check if arguments are properly provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./second number\n");
        exit(EXIT_FAILURE);
    }

    unsigned short int n = atoi(argv[1]);
    // printf("Number: %d\n", n);

    return EXIT_SUCCESS;
}

void evenOddParity(int n, int numberOfPairs)
{
    if (n % 2 == 0)
    {
        printf("Even-Parity\t%d\n", numberOfPairs);
    }
    else
    {
        printf("Odd-Parity\t%d\n", numberOfPairs);
    }
}