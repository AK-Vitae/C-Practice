#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 100 
#define MAXLINELENGTH 15 

int main(int argc, char *argv[])
{
    // Arguments not properly provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./interpret file.asm\n");
        exit(EXIT_FAILURE);
    }

    //  Read in the data and get the number of lines in the file
    int lineCount = 0;
    char lines[MAXLINES][MAXLINELENGTH];
    FILE *file = fopen(argv[1], "r");
    while(fgets(lines[lineCount], MAXLINELENGTH, file)) 
	{
        lines[lineCount][strlen(lines[lineCount]) - 1] = '\0';
        lineCount++;
    }

    fclose(file);

    printf("Number of lines: %d\n", lineCount);
    printf("The contents of the file are: \n");    
    for(int i = 0; i < lineCount; ++i)
    {
        printf("%s\n", lines[i]);
    }
    printf("\n");
}
