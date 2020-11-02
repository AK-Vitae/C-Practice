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

    
    int lineCount = 0;
    char ch;
    FILE *file = fopen(argv[1], "r");
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            lineCount++;
        }
    }
    char lines[lineCount][20];

    // Move file pointer to the start
    fseek(file, 0, SEEK_SET);
    
    fclose(file);

    printf("Number of lines: %d", lineCount);
}
