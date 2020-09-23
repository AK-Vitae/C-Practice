#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a node struct
typedef struct node
{
    int data;
    struct node *left, *right;
} bstNode;

// Prototypes
bstNode *newNode(int item);
void inorder(struct node *node);
bstNode *insert(bstNode *node, int value);
void freeBST(bstNode *node);

// Driver
int main(int argc, char *argv[])
{
    // File name argument not provided
    if (argc < 2)
    {
        fprintf(stderr, "Error\nProper Usage: ./bst filename.txt\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");

    // File name supplied but fopen failed
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open \'%s\'", argv[1]);
        exit(EXIT_FAILURE);
    }

    bstNode *root = NULL;

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
            root = insert(root, value);
        }
    }

    fclose(file);

    // Prints out BST in order
    inorder(root);

    // Free allocated memory
    freeBST(root);
}

// Create a node
bstNode *newNode(int item)
{
    bstNode *temp;
    temp = (bstNode *)malloc(sizeof(bstNode));
    temp->data = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Inorder Traversal
void inorder(bstNode *node)
{
    // Check to see if root or current node is null
    if (node != NULL)
    {
        // Travers left subtree for the smallest value
        inorder(node->left);

        // Print out current node
        printf("%d\t", node->data);

        // Traverse right subtree to get to larger values
        inorder(node->right);
    }
}

// Insert a node
bstNode *insert(bstNode *node, int value)
{
    // Returns the new node as it is the new root of the tree
    if (node == NULL)
    {
        return newNode(value);
    }

    // Traverse the left subtree
    if (value < node->data)
    {
        node->left = insert(node->left, value);
    }

    // Skip duplicate entries
    else if (value == node->data)
    {
        return node;
    }

    // Traverse the right subtree
    else
    {
        node->right = insert(node->right, value);
    }

    return node;
}

// Free the BST
void freeBST(bstNode *node)
{
    // Check to see if node is already freed
    if (node == NULL)
    {
        return;
    }

    // Recursively go through the left and right subtrees
    freeBST(node->left);
    freeBST(node->right);

    // Free the node
    free(node);
}