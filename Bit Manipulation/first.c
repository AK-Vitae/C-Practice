#include <stdio.h>
#include <stdlib.h>

// Prototypes
int set(int x, int n, int v);
void get(int x, int n);
int comp(int x, int n);

// Driver
int main(int argc, char *argv[])
{
    // Check if arguments are properly provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./first testfilename.txt\n");
        exit(EXIT_FAILURE);
    }

    // Read in value of number that is going to be manipulated
    int x;

    FILE *file = fopen(argv[1], "r");

    // File name supplied but fopen failed
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open \'%s\'", argv[1]);
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d\n", &x);
    // printf("Value: %d\n", x);

    // Read and run operations
    while (1)
    {
        int n, v;
        char operation[5];
        int inputPerLine = fscanf(file, "%s\t%d\t%d", operation, &n, &v);
        if (inputPerLine != 3)
        {
            break;
        }
        if (operation[0] == 's')
        {
            x = set(x, n, v);
            printf("%d\n", x);
        }
        else if (operation[0] == 'c')
        {
            x = comp(x, n);
            printf("%d\n", x);
        }
        else if (operation[0] == 'g')
        {
            get(x, n);
        }
    }

    fclose(file);

    return EXIT_SUCCESS;
}

// Sets the nth bit of the number x to v
int set(int x, int n, int v)
{
    // printf("SET: ");
    int temp = 1;
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
    return x;
}

// Returns the value of the nth bit of the number x
void get(int x, int n)
{
    // printf("GET: ");
    int temp = 1;
    temp = temp << n;
    printf("%d\n", (x & temp) && 1);
}

// Sets the value of the nth bit of x to its complement (1 if 0 and 0 otherwise)
int comp(int x, int n)
{
    // printf("COMP: ");
    int temp = 1;
    temp = temp << n;
    x = x ^ temp;
    return x;
}