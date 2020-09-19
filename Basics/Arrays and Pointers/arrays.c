//basic implementation of an array and pointers

#include <stdio.h>

void printArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main(int argc, char *argv[])
{
    int numbers[] = {3, 7, 11, 4, -2};
    int i;
    printf("Array size: %zu\n", sizeof(numbers) / sizeof(numbers[0]));
    printArray(numbers, 5);
    printf("\n");
    for ( i = 0; i < 5; i++)
    {
        printf("Address = %d\n", &numbers[i]);
        printf("Address = %d\n", numbers+i);
        printf("Value = %d\n", &numbers[i]);
        printf("Value = %d\n", *(numbers+i));
        printf("\n");
    }
    
}