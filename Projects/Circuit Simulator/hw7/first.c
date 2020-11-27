#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//gcc -Wall -fsanitize=address -std=c11 first.c -o first -lm
//./first test1.txt

struct directive
{
    char gate[17];
    int n;
    int s;
    int *inputs;
    int *outputs;
    int *selectors;
};

// Prototypes
int incrementInputs(int *arr, int icount);
void NOT(int *values, int iindex, int oindex);
void AND(int *values, int iindex1, int iindex2, int oindex);
void OR(int *values, int iindex1, int iindex2, int oindex);
void NAND(int *values, int iindex1, int iindex2, int oindex);
void NOR(int *values, int iindex1, int iindex2, int oindex);
void XOR(int *values, int iindex1, int iindex2, int oindex);
int indexOf(int size, char **arr, char *var);
void resetValues(int size, int *arr);

