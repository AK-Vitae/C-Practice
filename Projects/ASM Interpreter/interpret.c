#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 100
#define MAXLINELENGTH 15

int main(int argc, char *argv[])
{
    int a = 'a' - 97;
    int b = 'b' - 97;
    int c = 'c' - 97;
    int d = 'd' - 97;
    printf("a-97: %d\n", a);
    printf("a-97: %d\n", b);
    printf("a-97: %d\n", c);
    printf("a-97: %d\n", d);
    // Make if register method?

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
        int instructionLine = i;
        if (n == 1)
        {
            printf("Instruction %d: %s\n", instructionLine, instruction);
            // READ //
            if (strcmp(instruction, "read") == 0)
            {
                char reg[3];
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
                // if (strcmp(reg, "ax") == 0)
                // {
                //     scanf("%d", &ax);
                //     printf(" Register Name: %s\n", reg);
                //     printf(" Register Value: %d\n", ax);
                // }
                // else if (strcmp(reg, "bx") == 0)
                // {
                //     scanf("%d", &bx);
                //     printf(" Register Name: %s\n", reg);
                //     printf(" Register Value: %d\n", bx);
                // }
                // else if (strcmp(reg, "cx") == 0)
                // {
                //     scanf("%d", &cx);
                //     printf(" Register Name: %s\n", reg);
                //     printf(" Register Value: %d\n", cx);
                // }
                // else if (strcmp(reg, "dx") == 0)
                // {
                //     scanf("%d", &dx);
                //     printf(" Register Name: %s\n", reg);
                //     printf(" Register Value: %d\n", dx);
                // }
            }
            // PRINT //
            else if (strcmp(instruction, "print") == 0)
            {
                char reg[3];
                sscanf(lines[i], "%s %s", instruction, reg);

                // Use switch statement? with ASCII
                if (isdigit(reg[0]) != 0)
                {
                    printf(" Printed: %d\n", atoi(reg));
                }
                else
                {
                    int condition = (reg[0] - 97) + (reg[1] - 120);
                    switch (condition)
                    {
                    case 0:
                        printf(" Printed: %d\n", ax);
                        break;
                    case 1:
                        printf(" Printed: %d\n", bx);
                        break;
                    case 2:
                        printf(" Printed: %d\n", cx);
                        break;
                    case 3:
                        printf(" Printed: %d\n", dx);
                        break;
                    default:
                        printf("Output Error");
                        break;
                    }
                    // if (strcmp(reg, "ax") == 0)
                    // {
                    //     printf(" Printed: %d\n", ax);
                    // }
                    // else if (strcmp(reg, "bx") == 0)
                    // {
                    //     printf(" Printed: %d\n", bx);
                    // }
                    // else if (strcmp(reg, "cx") == 0)
                    // {
                    //     printf(" Printed: %d\n", cx);
                    // }
                    // else if (strcmp(reg, "dx") == 0)
                    // {
                    //     printf(" Printed: %d\n", dx);
                    // }
                }
            }
            // JUMPS //
            else if (strcmp(instruction, "jmp") == 0)
            {
                int jump;
                sscanf(lines[i], "%s %d", instruction, &jump);
                printf(" Jumped to line %d\n", jump);
                i = jump - 1;
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
                //whichRegister:
                //takes reg array and will return 0,1,2,3,4 which will be used in register switch case
                // 4 = default = atoi(reg)
                int jump;
                char reg1[3];
                char reg2[3];
                sscanf(lines[i], "%s %d %s %s", instruction, &jump, reg1, reg2);
                printf(" Jumped to line %d, %s %s\n", jump, reg1, reg2);
                if ((isdigit(reg1[0]) != 0) && (isdigit(reg2[0]) != 0))
                {
                    if (atoi(reg1) <= atoi(reg2))
                    {
                        i = jump - 1;
                    }
                }
                else if ((isdigit(reg1[0]) != 0))
                {
                    if (strcmp(reg2, "ax") == 0)
                    {
                        if (atoi(reg1) <= ax)
                        {
                            i = jump - 1;
                        }
                    }
                    else if (strcmp(reg2, "bx") == 0)
                    {
                        if (atoi(reg1) <= bx)
                        {
                            i = jump - 1;
                        }
                    }
                    else if (strcmp(reg2, "cx") == 0)
                    {
                        if (atoi(reg1) <= cx)
                        {
                            i = jump - 1;
                        }
                    }
                    else if (strcmp(reg2, "dx") == 0)
                    {
                        if (atoi(reg1) <= dx)
                        {
                            i = jump - 1;
                        }
                    }
                }
                else if ((isdigit(reg2[0]) != 0))
                {
                    if (strcmp(reg1, "ax") == 0)
                    {
                        printf("  reached here ax = %d <= 0, i = %d\n", ax, i);
                        if (ax <= atoi(reg2))
                        {
                            i = jump - 1;
                            printf("   Now i = %d\n", i);
                        }
                    }
                    else if (strcmp(reg1, "bx") == 0)
                    {
                        if (bx <= atoi(reg2))
                        {
                            i = jump - 1;
                        }
                    }
                    else if (strcmp(reg1, "cx") == 0)
                    {
                        if (cx <= atoi(reg2))
                        {
                            i = jump - 1;
                        }
                    }
                    else if (strcmp(reg1, "dx") == 0)
                    {
                        if (bx <= atoi(reg2))
                        {
                            i = jump - 1;
                        }
                    }
                }
                else if ((strcmp(reg1, "ax") == 0) && (strcmp(reg2, "bx") == 0))
                {
                    if (ax <= bx)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "ax") == 0) && (strcmp(reg2, "cx") == 0))
                {
                    if (ax <= cx)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "ax") == 0) && (strcmp(reg2, "dx") == 0))
                {
                    if (ax <= dx)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "bx") == 0) && (strcmp(reg2, "ax") == 0))
                {
                    if (bx <= ax)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "bx") == 0) && (strcmp(reg2, "cx") == 0))
                {
                    if (bx <= cx)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "bx") == 0) && (strcmp(reg2, "dx") == 0))
                {
                    if (bx <= dx)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "cx") == 0) && (strcmp(reg2, "ax") == 0))
                {
                    if (cx <= ax)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "cx") == 0) && (strcmp(reg2, "bx") == 0))
                {
                    if (cx <= bx)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "cx") == 0) && (strcmp(reg2, "dx") == 0))
                {
                    if (cx <= dx)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "dx") == 0) && (strcmp(reg2, "ax") == 0))
                {
                    if (dx <= ax)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "dx") == 0) && (strcmp(reg2, "bx") == 0))
                {
                    if (dx <= bx)
                    {
                        i = jump - 1;
                    }
                }
                else if ((strcmp(reg1, "dx") == 0) && (strcmp(reg2, "cx") == 0))
                {
                    if (dx <= cx)
                    {
                        i = jump - 1;
                    }
                }
            }
        }
        else
        {
            printf("Instruction %d: No operation\n", instructionLine);
        }
    }
}