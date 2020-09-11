# Fundamentals

## The General Form of a Simple Program

Example C program

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
```

Structure:

*directives*

int main(void)
{
	*statements*
}

### Directives

Example: #include <stdio.h>

- A directive states that the information in a "#..." is to be "included" into a program before it is compiled
- Directives always begin with a # character and by default are one line long



### Functions

Example: int main(void){ return 0}

- A series of statements that have been grouped together and given a name.
- Functions that compute something have a return statement
- C has library functions as well as ones that written by the programmer



### Statements

Example: printf("Hello, World!\n");

- A command to be executed when the program runs
- There can be return statements as well as function calls



## Variables and Assignment

- Every variable must have a type (int, float, etc.)
- Variables must be declared before they can be used (int height, float profit)
- When main contains declarations they must precede statements
- When printing put variables you need to organize where variable is being printed out.
- Example: printf("Height: %d Length: %d\n", height, length)
- Reading user input:
  - Integer: scanf("%d, &i");
  - Float: scanf("%f", &x);
- Macro definition: #define VARIABLE_IN_CAPS 50