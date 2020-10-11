#include <stdio.h>
#include <stdlib.h>

// Driver
int main(int argc, char *argv[])
{
    // Arguments not properly provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./first testfilename.txt\n");
        exit(EXIT_FAILURE);
    }

    int x;

    FILE *file = fopen(argv[1], "r");

    // File name supplied but fopen failed
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open \'%s\'", argv[1]);
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d\n", &x);
    printf("Value: %d\n", x);

    while (1)
    {
        int n, v, temp;
        char operation[5];
        int data = fscanf(file, "%s\t%d\t%d", operation, &n, &v);
        if (data != 3)
        {
            break;
        }
        if (operation[0] == 's')
        {
            printf("SET: ");
            temp = 1;
            temp = temp << n;
            if (!v)
            {
                temp = ~temp;
                x = x & temp;
            }
            else
            {
                x = x | temp;
            }
            printf("%d\n", x);
        }
        else if (operation[0] == 'c')
        {
            printf("COMP: ");
            temp = 1;
            temp = temp << n;
            x = x ^ temp;
            printf("%d\n", x);
        }
        else if (operation[0] == 'g')
        {
            printf("GET: ");
            temp = 1;
            temp = temp << n;
            printf("%d\n", (x & temp) && 1);
        }
    }

    fclose(file);
}
