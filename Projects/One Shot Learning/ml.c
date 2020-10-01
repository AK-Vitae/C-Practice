/* 
 * 
 * This code calculates the house price of a house by learning from
 * training data. It uses pseudo inverse of a given matrix to find the 
 * weight of different features.
 * 
 * Predicted Price : Y = W0 + W1*X1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)  
 * 
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 * 
 */

#include <stdio.h>
#include <stdlib.h>

// Prototypes
double **multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double **transposeMatrix(double **mat, int row, int col);
double **inverseMatrix(double **matA, int dimension);
void printMatrix(double **matrix, int row, int column);
void freeMemory(double **matrix, int row);


//gcc -Wall -fsanitize=address -o file* file*.c
//gcc -Wall -Werror -fsanitize=address ml.c -o ml
//./ml trainA.txt testA.txt

// Driver
int main(int argc, char **argv)
{
    // Arguments not properly provided
    if (argc < 3)
    {
        fprintf(stderr, "Error\nProper Usage: ./ml trainfilename.txt testfilename.txt\n");
        exit(EXIT_FAILURE);
    }

    // Read in Training Matrix Data //
    int rowTrain, columnTrain;

    FILE *fileTrain = fopen(argv[1], "r");

    // File name supplied but fopen failed
    if (fileTrain == NULL)
    {
        fprintf(stderr, "Error: Could not open \'%s\'", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Read in the number of attributes in the training data
    fscanf(fileTrain, "%d \n", &columnTrain);
    columnTrain++; // Account for the house price column in the training data
    // Read in the number of training data examples
    fscanf(fileTrain, "%d \n", &rowTrain);
    
    // Create Training Matrix
    double **matrixTrain = (double **)malloc(rowTrain * sizeof(double *));
    for (int i = 0; i < rowTrain; i++)
    {
        matrixTrain[i] = (double *)malloc(columnTrain * sizeof(double));
    }
    for (int i = 0; i < rowTrain; i++)
    {
        for (int j = 0; j < columnTrain; j++)
        {
            fscanf(fileTrain, "%lf,", &matrixTrain[i][j]);
        }
        fscanf(fileTrain, "\n");
    }
    fclose(fileTrain);

    printf("-------Training Matrix-------\n");
    printf("Rows: %d\n", rowTrain);
    printf("Columns: %d\n", columnTrain);
    printMatrix(matrixTrain, rowTrain, columnTrain);
    //freeMemory(matrixTrain, rowTrain);

    // Read in Testing Matrix Data //
    int rowTest, columnTest;

    FILE *fileTest = fopen(argv[2], "r");

    // File name supplied but fopen failed
    if (fileTest == NULL)
    {
        fprintf(stderr, "Error: Could not open \'%s\'", argv[2]);
        exit(EXIT_FAILURE);
    }

    fscanf(fileTest, "%d \n", &rowTest);
    columnTest = columnTrain - 1;

    // Create Training Matrix
    double **matrixTest = (double **)malloc(rowTest * sizeof(double *));

    for (int i = 0; i < rowTest; i++)
    {
        matrixTest[i] = (double *)malloc(columnTest * sizeof(double));
    }

    for (int i = 0; i < rowTest; i++)
    {
        for (int j = 0; j < columnTest; j++)
        {
            fscanf(fileTest, "%lf,", &matrixTest[i][j]);
        }
        fscanf(fileTest, "\n");
    }
    fclose(fileTest);

    printf("-------Testing Matrix-------\n");
    printf("Rows: %d\n", rowTest);
    printf("Columns: %d\n", columnTest);
    printMatrix(matrixTest, rowTest, columnTest);
    // freeMemory(matrixTest, rowTest);

    // Create Attribute Matrix: X, rowTrain, columnTrain
    double **X = (double **)malloc(rowTrain * sizeof(double *));

    for (int i = 0; i < rowTrain; i++)
    {
        X[i] = (double *)malloc(columnTrain * sizeof(double));
    }

    for (int i = 0; i < rowTrain; i++)
    {
        X[i][0] = 1;
        for (int j = 1; j < columnTrain; j++)
        {
            X[i][j] = matrixTrain[i][j - 1];
        }
    }

    printf("-------Attribute Matrix: X-------\n");
    printf("Rows: %d\n", rowTrain);
    printf("Columns: %d\n", columnTrain);
    printMatrix(X, rowTrain, columnTrain);

    // Create House Price Matrix: Y, rowTrain, 1
    double **Y = (double **)malloc(rowTrain * sizeof(double *));

    for (int i = 0; i < rowTrain; i++)
    {
        Y[i] = (double *)malloc(sizeof(double));
    }

    for (int i = 0; i < rowTrain; i++)
    {
        Y[i][0] = matrixTrain[i][columnTrain - 1];
    }

    printf("-------House Prices Matrix: Y-------\n");
    printf("Rows: %d\n", rowTrain);
    printf("Columns: 1\n");
    printMatrix(Y, rowTrain, 1);

}

double **multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double **result = malloc(r1 * sizeof(double *));

    // your code goes here

    return result;
}

double **transposeMatrix(double **mat, int row, int col)
{
    double **matTran = malloc(col * sizeof(double *));

    for (int i = 0; i < col; i++)
    {
        matTran[i] = (double *)malloc(row * sizeof(double));
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matTran[j][i] = mat[i][j];
        }
    }

    return matTran;
}

double **inverseMatrix(double **matA, int dimension)
{

    double **matI = malloc(dimension * sizeof(double *));

    // your code goes here

    return matI;
}

void printMatrix(double **matrix, int row, int column) 
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void freeMemory(double **matrix, int row)
{
    for (int i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}
