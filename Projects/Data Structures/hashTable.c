#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10000

// Define a node struct
typedef struct node
{
    int data;
    struct node *next;
} hashNode;

// Prototypes
int hash(int data);
void insert(int value);
void search(int value);
void freeTable(hashNode *table[]);

// Declare global hash table
hashNode *table[TABLE_SIZE] = {NULL};
int insertionCollisions = 0;
int nodeCount = 0;
int successfulSearches = 0;

// Driver
int main(int argc, char *argv[])
{
    // File name argument not provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./hashTable filename.txt\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");

    // File name supplied but fopen failed
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open \'%s\'", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Read in data:
    // i indicates a value insertion
    // s indicates a value search
    while (1)
    {
        int value;
        char c;
        int n = fscanf(file, " %c\t%d", &c, &value);
        if (n != 2)
        {
            break;
        }
        if (c == 'i')
        {
            insert(value);
        }
        else
        {
            if (c == 's')
            {
                search(value);
            }
        }
    }

    fclose(file);

    // Prints out the number of insertions where a collision occurred
    printf("%d\n", insertionCollisions);

    // Prints out the number of successful searches (where the value was present)
    printf("%d\n", successfulSearches);

    // Free allocated memory
    freeTable(table);
}


// Hash function: x % N where N = 10000
int hash(int data)
{
    int index;
    if (data < 0)
    {
        index = (data % TABLE_SIZE) + TABLE_SIZE;
    }
    else
    {
        index = data % TABLE_SIZE;
    }
    return index;
}

void insert(int value)
{
    int index = hash(value);
    hashNode *newNode;
    hashNode *current;
    newNode = (hashNode *)malloc(sizeof(hashNode));
    newNode->data = value;
    newNode->next = NULL;

    // Insert value into empty index
    if (table[index] == NULL)
    {
        table[index] = newNode;
        nodeCount++;
    }
    else
    {
        // Resolve collision via chaining
        current = table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
        nodeCount++;
        insertionCollisions++;
    }
}

void search(int value)
{
    int index = hash(value);
    hashNode *current;
    if (table[index] != NULL)
    {
        current = table[index];
        while (current != NULL)
        {
            if (current->data == value)
            {
                successfulSearches++;
                break;
            }
            current = current->next;
        }
    }
}


// Free the hash table
void freeTable(hashNode *table[])
{
    // Index traversal
    hashNode *current;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        current = table[i];
        while (current != NULL)
        {
            // Chain traversal
            hashNode *temp;
            temp = current;
            current = current->next;
            free(temp);
        }
    }
}
