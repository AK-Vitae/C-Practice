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
double **identityMatrix(double **matA, int dimension);
double **inverseMatrix(double **matA, double **identity, int dimension);
void printMatrix(double **matrix, int row, int column);
void freeMemory(double **matrix, int row);

// Compile: gcc -Wall -Werror -fsanitize=address ml.c -o ml
// Running with arguments: ./ml trainA.txt testA.txt

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

    // Create Training Matrix: matrixTrain, rowTrain, columnTrain
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
    columnTest = columnTrain;

    // Create Training Matrix
    double **matrixTest = (double **)malloc(rowTest * sizeof(double *));

    for (int i = 0; i < rowTest; i++)
    {
        matrixTest[i] = (double *)malloc(columnTest * sizeof(double));
    }

    for (int i = 0; i < rowTest; i++)
    {
        matrixTest[i][0] = 1.0;
        for (int j = 1; j < columnTest; j++)
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

    // Create Attribute Matrix: X, rowTrain, columnTrain
    double **X = (double **)malloc(rowTrain * sizeof(double *));

    for (int i = 0; i < rowTrain; i++)
    {
        X[i] = (double *)malloc(columnTrain * sizeof(double));
    }

    for (int i = 0; i < rowTrain; i++)
    {
        X[i][0] = 1.0;
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

    // Free training matrix as it is not required anymore
    freeMemory(matrixTrain, rowTrain);

    // Transposed Attribute Matrix: Xt, columnTrain, rowTrain
    printf("-------Attribute Matrix Transposed: Xt-------\n");
    printf("Rows: %d\n", columnTrain);
    printf("Columns: %d\n", rowTrain);
    double **transposedX = transposeMatrix(X, rowTrain, columnTrain);
    printMatrix(transposedX, columnTrain, rowTrain);

    // Product Matrix of Xt and X: XtX, columnTrain, columnTrain
    printf("-------Product Matrix of Xt and X: XtX-------\n");
    printf("Rows: %d\n", columnTrain);
    printf("Columns: %d\n", columnTrain);
    double **productTransposedX = multiplyMatrix(transposedX, X, columnTrain, rowTrain, rowTrain, columnTrain);
    printMatrix(productTransposedX, columnTrain, columnTrain);

    // Product Matrix of Xt and Y: XtY, columnTrain, 1
    printf("-------Product Matrix of Xt and Y: XtY-------\n");
    printf("Rows: %d\n", columnTrain);
    printf("Columns: %d\n", 1);
    double **productTransposedY = multiplyMatrix(transposedX, Y, columnTrain, rowTrain, rowTrain, 1);
    printMatrix(productTransposedY, columnTrain, 1);

    // Identity Matrix: identity, columnTrain, columnTrain
    printf("-------Identity Matrix-------\n");
    printf("Rows: %d\n", columnTrain);
    printf("Columns: %d\n", columnTrain);
    double **identity = identityMatrix(productTransposedX, columnTrain);
    printMatrix(identity, columnTrain, columnTrain);

    // Inverse Matrix of XtX: inverse, columnTrain, columnTrain
    printf("-------Inverse Matrix XtX^-1-------\n");
    printf("Rows: %d\n", columnTrain);
    printf("Columns: %d\n", columnTrain);
    double **inverse = inverseMatrix(productTransposedX, identity, columnTrain);
    printMatrix(inverse, columnTrain, columnTrain);

    // Weights Matrix: W,
    printf("-------Weights Matrix-------\n");
    printf("Rows: %d\n", columnTrain);
    printf("Columns: %d\n", 1);
    double **weights = multiplyMatrix(inverse, productTransposedY, columnTrain, columnTrain, columnTrain, 1);
    printMatrix(weights, columnTrain, 1);

    printf("-------Testing Matrix-------\n");
    printf("Rows: %d\n", rowTest);
    printf("Columns: %d\n", columnTest);
    printMatrix(matrixTest, rowTest, columnTest);

    // Calculate house prices
    double housePrice = 0;
    for (int i = 0; i < rowTest; i++)
    {
        for (int j = 0; j < columnTrain; j++)
        {
            housePrice += weights[j][0] * matrixTest[i][j];
        }
        printf("%0.0lf \n", housePrice);
        housePrice = 0;
    }

    // Free remaining allocated memory
    freeMemory(matrixTest, rowTest);
    freeMemory(X, rowTrain);
    freeMemory(Y, rowTrain);
    freeMemory(transposedX, columnTrain);
    freeMemory(productTransposedX, columnTrain);
    freeMemory(productTransposedY, columnTrain);
    freeMemory(identity, columnTrain);
    freeMemory(weights, columnTrain);
    // gcc ml.c -o ml
    // Compile: gcc -Wall -Werror -fsanitize=address ml.c -o ml
    // Running with arguments: ./ml trainA.txt testA.txt
}

double **multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    // Error handling
    if (c1 != r2)
    {
        printf("Error while trying to multiply matrices: The number of columns of the 1st matrix does not equal the number of rows of the 2nd matrix.");
        return NULL;
    }

    // Create 2d array of 0s
    double **result = (double **)calloc(r1, sizeof(double *));

    for (int i = 0; i < r1; i++)
    {
        result[i] = (double *)calloc(c2, sizeof(double));
    }

    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            for (int k = 0; k < c1; k++)
            {
                result[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }

    return result;
}

double **transposeMatrix(double **mat, int row, int col)
{
    double **matTran = (double **)malloc(col * sizeof(double *));

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

double **identityMatrix(double **matA, int dimension)
{
    // Make identity matrix
    double **identity = (double **)calloc(dimension, sizeof(double *));

    for (int i = 0; i < dimension; i++)
    {
        identity[i] = (double *)calloc(dimension, sizeof(double));
    }

    for (int i = 0; i < dimension; i++)
    {
        identity[i][i] = 1;
    }

    return identity;
}

double **inverseMatrix(double **matA, double **identity, int dimension)
{
    // matA and identity matrix arguments will be used as the augmented matrix
    double c;
    double p;

    for (int i = 0; i < dimension; i++)
    {
        for (int j = i; j < dimension; j++)
        {
            if (matA[j][i] != 0 && j != i)
            {
                p = matA[j][i];
                for (int k = 0; k < dimension; k++)
                {
                    matA[j][k] = matA[j][k] - (p * matA[i][k]);
                    identity[j][k] = identity[j][k] - (p * identity[i][k]);
                }
            }
            else if (matA[j][i] != 1 && j == i)
            {
                if (matA[j][i] != 0)
                {
                    c = matA[j][i];
                    for (int k = 0; k < dimension; k++)
                    {
                        matA[j][k] = matA[j][k] / c;
                        identity[j][k] = identity[j][k] / c;
                    }
                }
                else
                {
                    printf("Error: 0 in the pivot");
                }
            }
        }
    }

    for (int i = dimension - 1; i > -1; i--)
    {
        for (int j = i; j > -1; j--)
        {
            if (matA[j][i] != 0 && i != j)
            {
                c = matA[j][i];
                for (int k = 0; k < dimension; k++)
                {
                    matA[j][k] = matA[j][k] - (c * matA[i][k]);
                    identity[j][k] = identity[j][k] - (c * identity[i][k]);
                }
            }
            else if (matA[j][i] != 1 && i == j)
            {
                c = matA[j][i];
                matA[j][i] = matA[j][i] / c;
                identity[j][i] = identity[j][i] / c;
            }
        }
    }

    return identity;
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