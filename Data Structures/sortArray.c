#include <stdio.h>
#include <stdlib.h>

// Driver
int main(int argc, char *argv[])
{
    // Declared variables that will be used throughout the function
    int *arr, *brr, size, oddCount = 0;

    // File name argument not provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./sortArray filename.txt\n");
        exit(EXIT_FAILURE);
    }

    // Opens passed on file argument to read
    FILE *file = fopen(argv[1], "r");

    // File name supplied but fopen failed
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open \'%s\'", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Reads in size of array
    fscanf(file, "%d\n", &size);

    // Creates arrays
    arr = (int *)malloc(size * sizeof(int));
    brr = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        fscanf(file, "%d\t", &arr[i]);
        if (arr[i] % 2 != 0)
        {
            // Notes the number of odd numbers
            oddCount++;
        }
    }
    fclose(file);

    // Sorts entire array in ascending order
    for (int i = 0; i < size - 1; i++)
    {

        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Seperates the even and odd portions of the array
    int j = 0;
    int k = size - oddCount;
    int evenCount = k;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            if (j < size - oddCount)
                brr[j++] = arr[i];
        }
        else
        {
            if (k < size)
                brr[k++] = arr[i];
        }
    }

    for (int i = 0; i < size; i++)
    {
        arr[i] = brr[i];
    }

    // Makes the odd numbers go in descending order
    for (int i = evenCount, j = size - 1; i < j; i++, j--)
    {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    // Prints out array
    for (int i = 0; i < k; i++)
    {
        printf("%d\t", arr[i]);
    }

    // Free allocated memory
    free(arr);
    free(brr);
}