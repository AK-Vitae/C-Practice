#include <stdio.h>
#include <stdlib.h>
#define SIZE 16

// Prototypes
int get(unsigned short int x, int n);
void isPalindrome(unsigned short int n);

// Driver
int main(int argc, char *argv[])
{
    // Check if arguments are properly provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./third number\n");
        exit(EXIT_FAILURE);
    }

    unsigned short int n = atoi(argv[1]);
    // printf("Number: %d\n", n);

    isPalindrome(n);

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


// Checks to see if provided number's 16bit binary representation is a palindrome
void isPalindrome(unsigned short int n)
{
    int palindrome = 1;
    for (int i = 0; i < SIZE; i++)
    {
        if (get(n, i) != get(n, 15 - i))
        {
            palindrome = 0;
        }
    }

    if (palindrome == 1)
    {
        printf("Is-Palindrome\n");
    }
    else if (palindrome == 0)
    {
        printf("Not-Palindrome\n");
    }
}