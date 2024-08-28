#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/matrixLib.hpp"
#include "../include/perfomanceTestLib.hpp"
#include "../include/circleLib.hpp"

void classShowcase();
void testPerfomance();



int main() {
#ifdef TEST_PERFOMANCE
    testPerfomance();
#else
    classShowcase();
#endif

    // Circle circle;
    // initCircle(31, &circle);
    // printCircle(&circle);

    // Matrix matrix = {};
    // matrixInit(4, 4, &matrix);
    // matrixRead(&matrix);
    // matrixPrint(&matrix);
    // MatrixElem determ = getDetermine(&matrix);
    // printf("determ : %d\n", determ);

    return 0;
}

void testPerfomance() {
    Tester tester;
    int cntOfTests = 5;
    int low  = 1200;
    int high = 1400;
    //low = 300, high = 500;

    // don't put too big numbers with int type, beware of overflow,
    // if you have abs(number) < A, then numbers will go up to A ^ 3
    Randomizer randomizer = {-100, 100, low, high, low, high};
    generateTests(&tester, cntOfTests, &randomizer);

    long double dispWithout = 0;
    long double dispWith    = 0;
    long double meanArifmWithout = runOnTests(&tester, matricesMultiplyStandart, &dispWithout);
    long double meanArifmWith    = runOnTests(&tester, matricesMultiplyWithTranspon, &dispWith);

    printf("mean arifmetic time per test without transp: %.10Lg +- %.10Lg\n",
        meanArifmWithout, dispWithout);
    printf("mean arifmetic time per test with    transp: %.10Lg +- %.10Lg\n",
        meanArifmWith, dispWith);
    destructTester(&tester);
}

void classShowcase() {
//     Matrix matrix = {};
//     matrixInit(5, 4, &matrix);
//     matrixRead(&matrix);
//     matrixPrint(&matrix);
//
//     Matrix transpMatrix = {};
//     matrixInit(matrix.w, matrix.h, &transpMatrix);
//     matrixTranspon(&matrix, &transpMatrix);
//
//     printf("\n\ntranspon matrix:\n");
//     matrixPrint(&transpMatrix);
//
//     Matrix matrix_2 = {};
//     matrixInit(4, 7, &matrix_2);
//     matrixRead(&matrix_2);
//     matrixPrint(&matrix_2);
//
//     // ------------------------------       MATRIX MULT     ---------------------------------------
//
//     Matrix addResult = {};
//     matrixInit(matrix.h, matrix.w, &addResult);
//     matricesAdd(&matrix, &matrix, &addResult);
//     printf("\n\n addition result matrix:\n");
//     matrixPrint(&addResult);
//
//     // ------------------------------       MATRIX ADD     ---------------------------------------
//
//     Matrix multResult = {};
//     getMatrixMultipilcationSizes(&matrix, &matrix_2, &multResult.h, &multResult.w);
//     matrixInit(multResult.h, multResult.w, &multResult);
//     matricesMultiply(&matrix, &matrix_2, &multResult, NO_TRANSPONATION);
//     printf("\n\n multiplication result matrix:\n");
//     matrixPrint(&multResult);

    // ----------------------------------       MATRIX DETERM       ----------------------------------

    Matrix matrix = {};
    matrixInit(4, 4, &matrix);
    matrixRead(&matrix);
    matrixPrint(&matrix);
    MatrixElem determSlow = getDetermine(&matrix, SUPER_SLOW);
    MatrixElem determFast = getDetermine(&matrix, CUBIC);
    printf("determ slow: %d\n", determSlow);
    printf("determ fast: %d\n", determFast);
}

/*

1 2 3 4
9 8 3 1
5 9 2 20
5 3 2 8

matrix example:

1 2
3 4

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
