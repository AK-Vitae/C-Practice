#include <stdio.h>
#include <stdlib.h>
// Driver
int main(int argc, char* argv[])
{
    // Arguments not properly provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./first testfilename.txt\n");
        exit(EXIT_FAILURE);
    }
}
