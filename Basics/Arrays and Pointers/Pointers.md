# Pointers

* In most modern computers, main memory is divided into **bytes**, with each byte capable of storing eight bits of information.
* Each byte has a unique **address** to distinguish it from the other bytes in memory.
* We can store addresses in pointer variables.
  * When we store  the address of  a variable i in the pointer variable p, we say p "points to " i.
  * Pointer = address
  * Pointer variable = variable that can store an address
* Pointer variables are capable of pointing to **objects** of a certain type(int, double, char, memory, etc). 



## Address and Indirection Operators

* Initializing a pointer using "&" operator:

```c
int i, *p;
p = &i;

int i;
int *p = &i;

int i, *p = &i;
```

* Once a pointer variable points to an object, we can use the "*" operator to access what's stored in the object

```c
printf("%d\n", *p)
```

* printf will display the value of i, not the address of i
* As long as p points to i, *p is an alias for i.
* Not only does *p have the same value as i, but changing the value of *p also changes the value of i.

```c

    int a;
    int *p;
    a = 10;
    p = &a; // &a = address of a
    printf("%d\n", p); // prints out the address of a
    printf("%d\n", *p); // *p- value at address pointed by p
    printf("%d\n", &a); // prints out the address of a
    printf("\n");
    printf("a = %d\n", a);
    *p = 12; // dereferencing
    printf("a = %d\n", a);
    printf("\n");
    int b = 20;
    *p = b;
    printf("%d\n", p);
    printf("b = %d\n", b);
    printf("*p = %d\n", *p);
    printf("a = %d\n", a); //Put the value of b into a but does not change the address
    printf("%d\n", p);

```

