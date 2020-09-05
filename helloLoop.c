//Include Files
#include <stdio.h>
#include <stdlib.h>

//Declaration of global variables
char cMessage[] = "Hello\n";

int main (int argc, char **argv)
{
    //Declaration of local variables
    int i, count;
    
    count = atoi(argv[1]);
    for (i = 0; i < count; i++) {
        printf("Hello %d\n", i);
    }
}