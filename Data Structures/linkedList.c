#include <stdio.h>
#include <stdlib.h>

// Define a node struct
typedef struct node
{
    int data;
    struct node *next;
} intNode;

//Prototypes
intNode *insert(intNode *head, int value);
intNode *delete (intNode *head, int num);
void freeList(intNode *head);
void print(intNode *head);

// Driver
int main(int argc, char const *argv[])
{
    // File name argument not provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./linkedList filename.txt\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");

    // File name supplied but fopen failed
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open \'%s\'", argv[1]);
        exit(EXIT_FAILURE);
    }

    intNode *head = NULL;

    // Read in data:
    // i indicates a node insertion
    // d indicates a node deletion
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
            head = insert(head, value);
        }
        else
        {
            if (c == 'd')
            {
                head = delete (head, value);
            }
        }
    }

    fclose(file);

    // Print out the number of nodes and the values of nodes(each only displayed once)
    print(head);

    // Free allocated memory
    freeList(head);
}

intNode *insert(intNode *head, int value)
{
    intNode *newNode;
    intNode *current;
    intNode *previous;

    newNode = (intNode *)malloc(sizeof(intNode));
    newNode->data = value;
    newNode->next = NULL;

    // Insert node as the head
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        current = head;
        previous = head;

        // Traversal
        while (current != NULL && current->data < value)
        {
            previous = current;
            current = current->next;
        }

        // Insert node to the end of the linked list
        if (current == NULL)
        {
            previous->next = newNode;
        }
        else
        {
            // Insert node in the middle
            if (current != head)
            {
                newNode->next = current;
                previous->next = newNode;
            }
            // Insert node before the head
            else
            {
                newNode->next = current;
                head = newNode;
            }
        }
    }
    return head;
}

intNode *delete (intNode *head, int target)
{
    intNode *temp;
    intNode *current;
    intNode *previous;
    current = head;

    // Empty linked list
    if (head == NULL)
    {
        return head;
    }
    else
    {
        // Traverse to the end of the linked list or until target value is found
        while (current != NULL && current->data != target)
        {
            previous = current;
            current = current->next;
        }

        // Target value is not in the linked list
        if (current == NULL)
        {
            return head;
        }

        // Target is at the head of the linked list
        if (current == head)
        {
            temp = current;
            current = current->next;
            free(temp);
            head = current;
        }
        else
        {
            // Target is at the end of the linked list
            if (current->next == NULL)
            {
                free(current);
                previous->next = NULL;
            }

            // First occurence of the target is in the middle of the linked list
            else
            {
                previous->next = current->next;
                free(current);
            }
        }
    }
    return head;
}

// Free up any allocated memory in the linked list
void freeList(intNode *head)
{
    intNode *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print(intNode *head)
{
    intNode *current = head;
    intNode *count = head;

    // Prints out the number of nodes in the linked list
    int nodeCount = 0;

    // If the linked list is empty
    if (head == NULL)
    {
        printf("%d\n", nodeCount);
        printf("\n");
    }
    else
    {
        // Prints out the number of nodes in the linked list including duplicates
        while (count != NULL)
        {
            nodeCount++;
            count = count->next;
        }
        printf("%d\n", nodeCount);

        // Prints outs values in the linked list, with duplicate values only printed once
        int duplicate;
        while (current != NULL)
        {
            if (duplicate != current->data)
            {
                printf("%d\t", current->data);
                duplicate = current->data;
                current = current->next;
            }
            else
            {
                current = current->next;
            }
        }
    }
}
