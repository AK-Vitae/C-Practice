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
    while (fgets(lines[lineCount], MAXLINELENGTH, file))
    {
        lines[lineCount][strlen(lines[lineCount]) - 1] = '\0';
        lineCount++;
    }
    fclose(file);

    // Intialize potential registers
    int ax;
    int bx;
    int cx;
    int dx;

    // Carry out instructions
    for (int i = 0; i < lineCount; i++)
    {
        char instruction[5];
        int n = sscanf(lines[i], "%s", instruction);
        int instructionLine = i + 1;
        if (n == 1)
        {
            
            printf("Instruction %d: %s\n", instructionLine, instruction);
            if (strcmp(instruction, "read") == 0)
            {
                char reg[2];
                sscanf(lines[i], "%s %s", instruction, reg);

                if (strcmp(reg, "ax") == 0)
                {
                    scanf("%d", &ax);
                    printf(" Register Name: %s\n", reg);
                    printf(" Register Value: %d\n", ax);
                }
                else if (strcmp(reg, "bx") == 0)
                {
                    scanf("%d", &bx);
                    printf(" Register Name: %s\n", reg);
                    printf(" Register Value: %d\n", bx);
                }
                else if (strcmp(reg, "cx") == 0)
                {
                    scanf("%d", &cx);
                    printf(" Register Name: %s\n", reg);
                    printf(" Register Value: %d\n", cx);
                }
                else if (strcmp(reg, "dx") == 0)
                {
                    scanf("%d", &dx);
                    printf(" Register Name: %s\n", reg);
                    printf(" Register Value: %d\n", dx);
                }
            }
            else if (strcmp(instruction, "print") == 0)
            {
                char reg[2];
                sscanf(lines[i], "%s %s", instruction, reg);

                if (strcmp(reg, "ax") == 0)
                {
                    printf("%d", ax);
                }
                else if (strcmp(reg, "bx") == 0)
                {
                    printf("%d", bx);
                }
                else if (strcmp(reg, "cx") == 0)
                {
                    printf("%d", cx);
                }
                else if (strcmp(reg, "dx") == 0)
                {
                    printf("%d", dx);
                }
            }
        }
        else
        {
            printf("Instruction %d: No operation\n", instructionLine);
        }
    }
}
