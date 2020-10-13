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

    return EXIT_SUCCESS;
}