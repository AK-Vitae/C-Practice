// Checks numbers for repeated digits

#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    bool digit_seen[10] = {false};
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    while (n > 10)
    {
        digit = n % 10;
        if (digit_seen[digit])
        {
            break;
        }
        digit_seen[digit] = true;
        n /= 10;
    }

    if (n>10)
    {
        printf("Number has repeated digit\n");
    } else
        {
            printf("Number has no repeated digit\n");
        }
        
    return 0;
}