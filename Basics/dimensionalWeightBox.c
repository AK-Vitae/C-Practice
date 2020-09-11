#include <stdio.h>
#define INCHES_PER_POUND 166

int main(void)
{
    int height, length, width, volume, weight;

    printf("Enter length of the box: "); //Read user input
    scanf("%d", &length);
    printf("Enter width of the box: ");
    scanf("%d", &width);
    printf("Enter height of the box: ");
    scanf("%d", &height);

    volume = height * length * width;
    weight = (volume + INCHES_PER_POUND - 1) / 166;

    printf("Dimensions: %dx%dx%d\n", length, width, height);
    printf("Volume (cubic inches): %d\n", volume);
    printf("Dimensional weight(pounds): %d\n", weight);

    return 0;
}