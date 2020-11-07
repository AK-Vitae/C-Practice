#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
        char instruction[6];
        int n = sscanf(lines[i], "%s", instruction);
        int instructionLine = i + 1;
        if (n == 1)
        {
            printf("Instruction %d: %s\n", instructionLine, instruction);
            // READ //
            if (strcmp(instruction, "read") == 0)
            {
                char reg[3];
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
            // PRINT //
            else if (strcmp(instruction, "print") == 0)
            {
                char reg[3];
                sscanf(lines[i], "%s %s", instruction, reg);

                if (isdigit(reg[0]) != 0)
                {
                    printf(" Printed: %d\n", atoi(reg));
                }
                else
                {
                    if (strcmp(reg, "ax") == 0)
                    {
                        printf(" Printed: %d\n", ax);
                    }
                    else if (strcmp(reg, "bx") == 0)
                    {
                        printf(" Printed: %d\n", bx);
                    }
                    else if (strcmp(reg, "cx") == 0)
                    {
                        printf(" Printed: %d\n", cx);
                    }
                    else if (strcmp(reg, "dx") == 0)
                    {
                        printf(" Printed: %d\n", dx);
                    }
                }
            }
            // JUMPS //
            else if (strcmp(instruction, "jmp") == 0)
            {

            }
            else if (strcmp(instruction, "je") == 0)
            {

            }
            else if (strcmp(instruction, "jne") == 0)
            {

            }
            else if (strcmp(instruction, "jg") == 0)
            {

            }
            else if (strcmp(instruction, "jge") == 0)
            {

            }
            else if (strcmp(instruction, "jl") == 0)
            {

            }
            else if (strcmp(instruction, "jle") == 0)
            {

            }
        }
        else
        {
            printf("Instruction %d: No operation\n", instructionLine);
        }
    }
}