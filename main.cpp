#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "matrixLib.hpp"





int main() {
    printf("Hello world!\n");

    Matrix matrix = {};
    initMatrix(5, 4, &matrix);
    readMatrix(&matrix);
    printMatrix(&matrix);
    Matrix transpMatrix = {};
    transponMatrix(&matrix, &transpMatrix);

    printf("\n\ntranspon matrix:\n");
    printMatrix(&transpMatrix);

    Matrix matrix_2 = {};
    initMatrix(4, 7, &matrix_2);
    readMatrix(&matrix_2);
    Matrix multResult = {};
    multiplyMatrixes(&matrix, &matrix_2, &multResult);
    printf("\n\n multiplication result matrix:\n");
    printMatrix(&multResult);

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
