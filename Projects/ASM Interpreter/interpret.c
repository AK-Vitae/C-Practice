#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 100
#define MAXLINELENGTH 20

//Prototypes
int getValue(char reg[], int ax, int bx, int cx, int dx);

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
        lines[lineCount][strlen(lines[lineCount])] = '\0';
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
        int instructionLine = i;
        if (n == 1)
        {
            // printf("Instruction %d: %s\n", instructionLine, instruction);
            // READ //
            if (strcmp(instruction, "read") == 0)
            {
                char reg[10];
                sscanf(lines[i], "%s %s", instruction, reg);

                int condition = (reg[0] - 97) + (reg[1] - 120); // a = 97, b = 98, c = 99, d = 100, x = 120
                switch (condition)
                {
                case 0:
                    scanf("%d", &ax);
                    break;
                case 1:
                    scanf("%d", &bx);
                    break;
                case 2:
                    scanf("%d", &cx);
                    break;
                case 3:
                    scanf("%d", &dx);
                    break;
                default:
                    printf("Invalid register");
                    break;
                }
            }
            // PRINT //
            else if (strcmp(instruction, "print") == 0)
            {
                char reg[10];
                sscanf(lines[i], "%s %s", instruction, reg);

                if (isdigit(reg[0]) != 0)
                {
                    int value;
                    sscanf(reg, "%d", &value);
                    printf("%d", value);
                }
                else
                {
                    int condition = (reg[0] - 97) + (reg[1] - 120);
                    switch (condition)
                    {
                    case 0:
                        printf("%d", ax);
                        break;
                    case 1:
                        printf("%d", bx);
                        break;
                    case 2:
                        printf("%d", cx);
                        break;
                    case 3:
                        printf("%d", dx);
                        break;
                    default:
                        printf("Print Error");
                        break;
                    }
                }
            }
            // Move //
            else if (strcmp(instruction, "mov") == 0)
            {
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %s %s", instruction, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);

                int condition = (reg2[0] - 97) + (reg2[1] - 120);
                switch (condition)
                {
                case 0:
                    ax = x;
                    break;
                case 1:
                    bx = x;
                    break;
                case 2:
                    cx = x;
                    break;
                case 3:
                    dx = x;
                    break;
                default:
                    printf("Movement Error");
                    break;
                }
            }
            // ARITHMETIC //
            else if (strcmp(instruction, "add") == 0)
            {
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %s %s", instruction, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);

                int condition = (reg2[0] - 97) + (reg2[1] - 120);
                switch (condition)
                {
                case 0:
                    ax = ax + x;
                    break;
                case 1:
                    bx = bx + x;
                    break;
                case 2:
                    cx = cx + x;
                    break;
                case 3:
                    dx = dx + x;
                    break;
                default:
                    printf("Addition Error");
                    break;
                }
            }

            else if (strcmp(instruction, "sub") == 0)
            {
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %s %s", instruction, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);

                int condition = (reg2[0] - 97) + (reg2[1] - 120);
                switch (condition)
                {
                case 0:
                    ax = ax - x;
                    break;
                case 1:
                    bx = bx - x;
                    break;
                case 2:
                    cx = cx - x;
                    break;
                case 3:
                    dx = dx - x;
                    break;
                default:
                    printf("Subtraction Error");
                    break;
                }
            }

            else if (strcmp(instruction, "mul") == 0)
            {
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %s %s", instruction, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);

                int condition = (reg2[0] - 97) + (reg2[1] - 120);
                switch (condition)
                {
                case 0:
                    ax = ax * x;
                    break;
                case 1:
                    bx = bx * x;
                    break;
                case 2:
                    cx = cx * x;
                    break;
                case 3:
                    dx = dx * x;
                    break;
                default:
                    printf("Mutliplication Error");
                    break;
                }
            }

            else if (strcmp(instruction, "div") == 0)
            {
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %s %s", instruction, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);

                int condition = (reg2[0] - 97) + (reg2[1] - 120);
                switch (condition)
                {
                case 0:
                    ax = x / ax;
                    break;
                case 1:
                    bx = x / bx;
                    break;
                case 2:
                    cx = x / cx;
                    break;
                case 3:
                    dx = x / dx;
                    break;
                default:
                    printf("Division Error");
                    break;
                }
            }
            // JUMPS //
            else if (strcmp(instruction, "jmp") == 0)
            {
                int jump;
                sscanf(lines[i], "%s %d", instruction, &jump);
                // printf(" Jumped to line %d\n", jump);
                i = jump - 1;
            }
            else if (strcmp(instruction, "je") == 0)
            {
                int jump;
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %d %s %s", instruction, &jump, reg1, reg2);
                // printf(" Jumped to line %d, %s %s\n", jump, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);
                int y = getValue(reg2, ax, bx, cx, dx);

                if (x = y)
                {
                    i = jump - 1;
                }
            }
            else if (strcmp(instruction, "jne") == 0)
            {
                int jump;
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %d %s %s", instruction, &jump, reg1, reg2);
                // printf(" Jumped to line %d, %s %s\n", jump, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);
                int y = getValue(reg2, ax, bx, cx, dx);

                if (x != y)
                {
                    i = jump - 1;
                }
            }
            else if (strcmp(instruction, "jg") == 0)
            {
                int jump;
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %d %s %s", instruction, &jump, reg1, reg2);
                // printf(" Jumped to line %d, %s %s\n", jump, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);
                int y = getValue(reg2, ax, bx, cx, dx);

                if (x > y)
                {
                    i = jump - 1;
                }
            }
            else if (strcmp(instruction, "jge") == 0)
            {
                int jump;
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %d %s %s", instruction, &jump, reg1, reg2);
                // printf(" Jumped to line %d, %s %s\n", jump, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);
                int y = getValue(reg2, ax, bx, cx, dx);

                if (x >= y)
                {
                    i = jump - 1;
                }
            }
            else if (strcmp(instruction, "jl") == 0)
            {
                int jump;
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %d %s %s", instruction, &jump, reg1, reg2);
                // printf(" Jumped to line %d, %s %s\n", jump, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);
                int y = getValue(reg2, ax, bx, cx, dx);

                if (x < y)
                {
                    i = jump - 1;
                }
            }
            else if (strcmp(instruction, "jle") == 0)
            {
                int jump;
                char reg1[10];
                char reg2[10];
                sscanf(lines[i], "%s %d %s %s", instruction, &jump, reg1, reg2);
                // printf(" Jumped to line %d, %s %s\n", jump, reg1, reg2);

                int x = getValue(reg1, ax, bx, cx, dx);
                int y = getValue(reg2, ax, bx, cx, dx);

                if (x <= y)
                {
                    i = jump - 1;
                }
            }
        }
        else
        {
            // printf("Instruction %d: No operation\n", instructionLine);
        }
    }
}

int getValue(char reg[], int ax, int bx, int cx, int dx)
{
    if ((isdigit(reg[0]) != 0))
    {
        int value;
        sscanf(reg, "%d", &value);
        return value; // Integer Value
    }
    int condition = (reg[0] - 97) + (reg[1] - 120);
    switch (condition)
    {
    case 0:
        return ax; // ax
        break;
    case 1:
        return bx; // bx
        break;
    case 2:
        return cx; // cx
        break;
    case 3:
        return dx; // dx
        break;
    default:
        printf("ERROR in determining register type");
        break;
    }
}