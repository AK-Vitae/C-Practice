#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Cache struct
typedef struct Cache
{
    unsigned int valid;
    unsigned long int tag;
    unsigned int time;
    struct Cache *next;
} Cache;

// Prototypes
int isPowerOfTwo(int n);
Cache **makeCache(int numberOfSets, int n);
void freeCache(Cache **cache, int numberOfSets);
void read(Cache **cache, unsigned long tag, int index, int sets, int n, int blockSize, unsigned long int address);
void write(Cache **cache, unsigned long tag, int index, int sets, int n, int blockSize, unsigned long int address);

// Global Variables
int reads = 0;
int writes = 0;
int hits = 0;
int misses = 0;

// Compile: gcc -Wall -fsanitize=address -std=c11 first.c -o first -lm

// Driver
int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 6)
    {
        fprintf(stderr, "Error: Proper Usage: ./first <cache size> <associativity> <replace policy> <block size> <trace file>\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[5], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open \'%s\'", argv[5]);
        exit(EXIT_FAILURE);
    }

    int cacheSize = atoi(argv[1]);
    int blockSize = atoi(argv[4]);
    int nAssoc = 0;
    int nSet = 0;

    // Check Validity of arguments
    int validFlag = true;
    // Check if cache size is a power of 2
    if (isPowerOfTwo(cacheSize) == 0)
    {
        fprintf(stderr, "Error: Cache Size is not a power of 2.\n");
        validFlag = false;
    }
    // Check if associativity argument is correct and change nAssoc accordingly
    if (strcmp(argv[2], "direct") == 0)
    {
        nSet = cacheSize / blockSize;
        nAssoc = 1;
    }
    else if (strcmp(argv[2], "assoc") == 0)
    {
        nSet = 1;
        nAssoc = cacheSize / blockSize;
    }
    else if (strncmp(argv[2], "assoc:", 6) == 0)
    {
        sscanf(argv[2], "assoc:%d", &nAssoc);
        // Check if n in assoc:n is a power of 2.
        if (isPowerOfTwo(nAssoc) == 0)
        {
            validFlag = false;
            printf("Error: n in assoc:n is not a power of 2.\n");
        }
        nSet = cacheSize / (blockSize * nAssoc);
    }
    else
    {
        printf("Error: Associativity should be direct, assoc, or assoc:n.\n");
        validFlag = false;
    }
    // Check if replacement policy is either lru or fifo
    if (strcmp(argv[3], "lru") != 0)
    {
        if (strcmp(argv[3], "fifo") != 0)
        {
            fprintf(stderr, "Error: Replacement policy should be lru or fifo.\n");
            validFlag = false;
        }
    }
    // Check if block size is a power of 2
    if (isPowerOfTwo(blockSize) == 0)
    {
        fprintf(stderr, "Error: Block Size is not a power of 2.\n");
        validFlag = false;
    }

    if (validFlag == false)
    {
        exit(EXIT_FAILURE);
    }

    // printf("File Opened No Errors\n");

    Cache **cache = makeCache(nSet, nAssoc);

    unsigned long int address = 0;
    char operation = ' ';
    while ((fscanf(file, "%c %lx\n", &operation, &address) != EOF && operation != '#'))
    {
        unsigned int setIndex = (address >> ((int)(log(blockSize) / log(2)))) & ((1 << ((int)(log(nSet) / log(2)))) - 1);
        unsigned long tag = (address >> ((int)(log(blockSize) / log(2)))) >> ((int)(log(nSet) / log(2)));
        if (operation == 'R')
        {
            read(cache, tag, setIndex, nSet, nAssoc, blockSize, address);
        }
        else if (operation == 'W')
        {
            write(cache, tag, setIndex, nSet, nAssoc, blockSize, address);
        }
    }
    fclose(file);

    printf("Memory reads: %d\n", reads);
    printf("Memory writes: %d\n", writes);
    printf("Cache hits: %d\n", hits);
    printf("Cache misses: %d\n", misses);

    freeCache(cache, nSet);
}
int isPowerOfTwo(int n)
{
    if (n == 0)
    {
        return 0;
    }

    while (n != 1)
    {
        if (n % 2 != 0)
        {
            return 0;
        }
        n = n / 2;
    }
    return 1;
}

Cache **makeCache(int numberOfSets, int n)
{
    Cache **temp = malloc(sizeof(struct Cache) * numberOfSets);
    for (int i = 0; i < numberOfSets; i++)
    {
        temp[i] = malloc(sizeof(struct Cache) * n);
        for (int j = 0; j < n; j++)
        {
            temp[i][j].valid = 0;
        }
    }
    return temp;
}

void freeCache(Cache **cache, int numberOfSets)
{
    for (int i = 0; i < numberOfSets; i++)
    {
        free(cache[i]);
    }
    free(cache);
}

void read(Cache **cache, unsigned long tag, int index, int sets, int n, int blockSize, unsigned long int address)
{
    int flag = false;
    for (int i = 0; i < n; i++)
    {
        if (cache[index][i].valid == 1 && cache[index][i].tag == tag)
        {
            flag = true;
            hits++;
            break;
        }
    }
    if (flag == true)
    {
        return;
    }
    else
    {
        misses++;
        reads++;
        int full = true;
        for (int i = 0; i < n; i++)
        {
            if (cache[index][i].valid == 1)
            {
                cache[index][i].time++;
            }
            if (cache[index][i].valid == 0)
            {
                full = false;
                break;
            }
        }
        int max = 0;
        if (full == true)
        {
            int i = 0;
            while (i < n)
            {
                if (cache[index][i].time > max)
                {
                    max = cache[index][i].time;
                }
                i++;
            }

            int j = 0;
            while (j < n)
            {
                if (cache[index][j].time == max)
                {
                    cache[index][j].valid = 0;
                    cache[index][j].tag = (-1);
                    cache[index][j].time = 0;
                    break;
                }
                j++;
            }
        }
        int i = 0;
        while (i < n)
        {
            if (cache[index][i].valid == 0)
            {
                cache[index][i].valid = 1;
                cache[index][i].tag = tag;
            }
            i++;
        }
    }
}

void write(Cache **cache, unsigned long tag, int index, int sets, int n, int blockSize, unsigned long int address)
{

    int flag = false;
    for (int i = 0; i < n; i++)
    {
        if (cache[index][i].valid == 1 && cache[index][i].tag == tag)
        {
            flag = true;
            hits++;
            writes++;
            break;
        }
    }
    if (flag == true)
    {
        return;
    }
    else
    {
        read(cache, tag, index, sets, n, blockSize, address);
        writes++;
        return;
    }
}