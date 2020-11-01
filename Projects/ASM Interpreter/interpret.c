#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Arguments not properly provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./interpret file.asm\n");
        exit(EXIT_FAILURE);
    }

    char lines[100][20];
    int lineCount = 0;
    FILE *file = fopen(argv[1], "r");

    fseek(file, 0, SEEK_END);
    fclose(file);
}
