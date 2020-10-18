#include <stdio.h>
#include <stdlib.h>
#define SIZE 16 // 16bit

// Prototypes
int get(unsigned short int x, int n);
void findParity(int numberOfOneBits, int numberOfPairs);

// Driver
int main(int argc, char *argv[])
{
    // Check if arguments are properly provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./second number\n");
        exit(EXIT_FAILURE);
    }

    unsigned short int n = atoi(argv[1]);
    // printf("Number: %d\n", n);

    int pairCount = 0;
    int oneCount = 0;
    int curr;
    int prev = 0;

    // Iterate through binary representation and find 1s and 1 pairs
    for (int i = 0; i < SIZE; i++)
    {
        curr = get(n, i);
        if (prev == 1 && curr == 1)
        {
            pairCount++;
            prev = 0;
        }
        else
        {
            prev = curr;
        }
        if (curr == 1)
        {
            oneCount++;
        }
    }

    findParity(oneCount, pairCount);
    
    return EXIT_SUCCESS;
}

// Returns the value of the nth bit of the number x
int get(unsigned short int x, int n)
{
    // printf("GET: ");
    int temp = 1;
    temp = temp << n;
    return ((x & temp) && 1);
}

// Given the number of 1 bits this method will determine parity
void findParity(int numberOfOneBits, int numberOfPairs)
{
    if (numberOfOneBits % 2 == 0)
    {
        printf("Even-Parity\t%d\n", numberOfPairs);
    }
    else
    {
        printf("Odd-Parity\t%d\n", numberOfPairs);
    }
}