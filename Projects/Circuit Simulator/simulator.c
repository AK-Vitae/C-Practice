#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//gcc -Wall -fsanitize=address -std=c11 first.c -o first -lm
//./simulator test1.txt
typedef struct Directive
{
    char block[17];
    int *inputs;
    int *outputs;
} Directive;

// Prototypes
int incrementInputs(int *arr, int icount);
void NOT(int *arr, int inputIndex, int outputIndex);
void doLogic(char block[], int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex);
int indexOf(int size, char **arr, char *var);

// Driver
int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Error: Proper Usage: ./simulator test.txt\n");
        exit(EXIT_FAILURE);
    }

    // Get file and check if it could be opened
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open \'%s\'", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Initialize circuit variables
    Directive *steps = NULL;
    int stepCount = 0, inputCount = 0, outputCount = 0, size = 2;
    char inputOutput[17];
    char **varNames;
    int *values = malloc(size * sizeof(int));

    // Read in input information
    fscanf(file, " %s", inputOutput);
    fscanf(file, "%d", &inputCount);

    varNames = malloc((inputCount + 2) * sizeof(char *));
    varNames[0] = "0\0";
    varNames[1] = "1\0";

    int i = 0;
    while (i < inputCount)
    {
        varNames[i + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%*[: ]%16s", varNames[i + 2]);
        i++;
    }

    // Read in output information
    fscanf(file, " %s", inputOutput);
    fscanf(file, "%d", &outputCount);
    size = size + outputCount + inputCount;
    varNames = realloc(varNames, size * sizeof(char *));

    i = 0;
    while (i < outputCount)
    {
        varNames[i + inputCount + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%*[: ]%16s", varNames[i + inputCount + 2]);
        i++;
    }

    // Organize all the steps in input file
    while (!feof(file))
    {
        int numInputs = 2, numOutputs = 1;
        Directive step;
        int sc = fscanf(file, " %s", inputOutput);
        if (sc != 1)
        {
            break;
        }
        stepCount++;
        strcpy(step.block, inputOutput);

        if (strcmp(inputOutput, "NOT") == 0)
        {
            numInputs = 1;
        }

        step.inputs = malloc(numInputs * sizeof(int));
        step.outputs = malloc(numOutputs * sizeof(int));

        char v[17];
        for (int i = 0; i < numInputs; i++)
        {
            fscanf(file, "%*[: ]%16s", v);
            step.inputs[i] = indexOf(size, varNames, v);
        }

        int j = 0;
        while (j < numOutputs)
        {
            fscanf(file, "%*[: ]%16s", v);
            int index = indexOf(size, varNames, v);
            if (index == -1)
            {
                size++;
                varNames = realloc(varNames, size * sizeof(char *));
                varNames[size - 1] = malloc(17 * sizeof(char));
                strcpy(varNames[size - 1], v);
                step.outputs[j] = size - 1;
            }
            else
            {
                step.outputs[j] = index;
            }
            j++;
        }

        // Populate list of steps
        if (!steps)
        {
            steps = malloc(sizeof(struct Directive));
        }
        else
        {
            steps = realloc(steps, stepCount * sizeof(struct Directive));
        }
        steps[stepCount - 1] = step;
    }

    int *inputsAndOutputs = calloc(size, sizeof(int));
    inputsAndOutputs[1] = 1;

    while (1)
    {
        // Print Inputs
        for (int i = 0; i < inputCount; i++)
        {
            printf("%d ", inputsAndOutputs[i + 2]);
        }
        for (int i = 0; i < stepCount; i++)
        {
            Directive step = steps[i];
            if (strcmp(step.block, "NOT") == 0)
            {
                NOT(inputsAndOutputs, step.inputs[0], step.outputs[0]);
            }
            else
            {
                doLogic(step.block, inputsAndOutputs, step.inputs[0], step.inputs[1], step.outputs[0]);
            }
        }

        // Print Outputs
        for (int i = 0; i < outputCount; i++)
        {
            printf("%d ", inputsAndOutputs[inputCount + i + 2]);
        }
        printf("\n");

        if (incrementInputs(inputsAndOutputs, inputCount))
        {
            break;
        }
    }

    // Free all allocated memory
    free(values);
    free(inputsAndOutputs);

    for (int i = 2; i < size; i++)
    {
        free(varNames[i]);
    }
    free(varNames);

    for (int i = 0; i < stepCount; i++)
    {
        free(steps[i].inputs);
        free(steps[i].outputs);
    }
    free(steps);
    fclose(file);

    exit(EXIT_SUCCESS);
}

int incrementInputs(int *arr, int inputCount)
{
    int i = inputCount + 1;
    while (i >= 2)
    {
        arr[i] = !arr[i];
        if (arr[i] == 1)
        {
            return 0;
        }
        i--;
    }
    return 1;
}

void NOT(int *arr, int inputIndex, int outputIndex)
{
    arr[outputIndex] = !arr[inputIndex];
}

void doLogic(char block[], int *arr, int inputIndexOne, int inputIndexTwo, int outputIndex)
{
    if (strcmp(block, "AND") == 0)
    {
        arr[outputIndex] = arr[inputIndexOne] && arr[inputIndexTwo];
    }
    if (strcmp(block, "OR") == 0)
    {
        arr[outputIndex] = arr[inputIndexOne] || arr[inputIndexTwo];
    }
    if (strcmp(block, "NAND") == 0)
    {
        arr[outputIndex] = !(arr[inputIndexOne] && arr[inputIndexTwo]);
    }
    if (strcmp(block, "NOR") == 0)
    {
        arr[outputIndex] = !(arr[inputIndexOne] || arr[inputIndexTwo]);
    }
    if (strcmp(block, "XOR") == 0)
    {
        arr[outputIndex] = arr[inputIndexOne] ^ arr[inputIndexTwo];
    }
}

int indexOf(int size, char **arr, char *var)
{
    int i = 0;
    while (i < size)
    {
        if (strcmp(arr[i], var) == 0)
        {
            return i;
        }
        i++;
    }
    return -1;
}
