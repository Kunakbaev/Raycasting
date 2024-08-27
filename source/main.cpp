#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/matrixLib.hpp"
#include "../include/memoryBufferLib.hpp"





int main() {
    printf("Hello world!\n");

    Matrix matrix = {};
    matrixInit(5, 4, &matrix);
    matrixRead(&matrix);
    matrixPrint(&matrix);
    Matrix transpMatrix = {};
    matrixInit(matrix.w, matrix.h, &transpMatrix);
    matrixTranspon(&matrix, &transpMatrix);

    printf("\n\ntranspon matrix:\n");
    matrixPrint(&transpMatrix);

    Matrix matrix_2 = {};
    matrixInit(4, 7, &matrix_2);
    matrixRead(&matrix_2);
    matrixPrint(&matrix_2);

    Matrix multResult = {};
    getMatrixMultipilcationSizes(&matrix, &matrix_2, &multResult.h, &multResult.w);
    matrixInit(multResult.h, multResult.w, &multResult);
    matricesMultiply(&matrix, &matrix_2, &multResult, NO_TRANSPONATION);
    printf("\n\n multiplication result matrix:\n");
    matrixPrint(&multResult);



    freeMemory(&multResult);
    freeMemory(&matrix);
    freeMemory(&matrix_2);
    freeMemory(&transpMatrix);

    return 0;
}

/*

matrix example:

11 12 13 14
21 22 23 23
31 32 33 34
41 42 43 44
51 52 53 54

11 12 13 14 15 16 17
21 22 23 24 25 26 27
31 32 33 34 35 36 37
41 42 43 44 45 46 47


*/
