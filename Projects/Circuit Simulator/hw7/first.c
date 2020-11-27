#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//gcc -Wall -fsanitize=address -std=c11 first.c -o first -lm
//./first test1.txt

typedef struct Directive
{
    char block[16];
    int n;
    int s;
    int *inputs;
    int *outputs;
    int *selectors;
} Directive;

// Prototypes
int incrementInputs(int *arr, int icount);
void not(int *arr, int inputIndex, int outputIndex);
void and (int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex);
void or (int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex);
void nand(int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex);
void nor(int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex);
void xor (int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex);
int indexOf(int size, char **arr, char *var);

int incrementInputs(int *arr, int icount)
{
    for (int i = icount + 1; i >= 2; i--)
    {
        arr[i] = !arr[i];
        if (arr[i] == 1)
        {
            return 1;
        }
    }
    return 0;
}

void not(int *arr, int inputIndex, int outputIndex)
{
    arr[inputIndex] = !arr[outputIndex];
}

void and (int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex)
{
    arr[outputIndex] = arr[inputIndexOne] && arr[inputIndexTwo];
}

void or (int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex)
{
    arr[outputIndex] = arr[inputIndexOne] || arr[inputIndexTwo];
}

void nand(int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex)
{
    arr[outputIndex] = !(arr[inputIndexOne] && arr[inputIndexTwo]);
}

void nor(int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex)
{
    arr[outputIndex] = !(arr[inputIndexOne] || arr[inputIndexTwo]);
}

void xor (int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex) {
    arr[outputIndex] = arr[inputIndexOne] ^ arr[inputIndexTwo];
}

    int indexOf(int size, char **arr, char *var)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(arr[i], var) == 0)
        {
            return i;
        }
    }
    return -1;
}
