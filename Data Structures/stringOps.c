#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototype
int isVowel(char);

// Driver
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error: Please enter a string of space separated words");
        return 0;
    }

    // Declared variables that will be used throughout the function
    char *str;
    int size = 1;

    // Determine the size of the inputted string
    for (int i = 1; i < argc; i++)
    {
        size += strlen(argv[i]) + 1;
    }

    str = (char *)malloc(size);

    // Concatenate each string argument together
    size = 0;
    for (int i = 1; i < argc; i++)
    {
        size += sprintf(str + size, "%s", argv[i]);

        //Assigns null terminator to end
        assert(str[size] == '\0');
    }

    // Check string for vowels, and if it is a vowel then add it to a temp char array
    char temp[10000];
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isVowel(str[i]) == 1)
        {
            temp[index] = str[i];
            index++;
        }
    }

    // Define where the string will end with null terminator
    temp[index] = '\0';

    // Copy the vowel only string back into the original string
    strcpy(str, temp);

    // Print out the vowels from inputted string
    printf("%s", str);

    // Free allocated memory
    free(str);
}

int isVowel(char ch)
{
    // Check upper and lower cases
    if (ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E' || ch == 'i' || ch == 'I' || ch == 'o' || ch == 'O' || ch == 'u' || ch == 'U')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}