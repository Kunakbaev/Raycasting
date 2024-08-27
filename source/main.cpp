#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/matrixLib.hpp"
#include "../include/perfomanceTestLib.hpp"
#include "../include/circleLib.hpp"

void classShowcase();
void testPerfomance();



int main() {
// #ifdef TEST_PERFOMANCE
//     testPerfomance();
// #else
//     classShowcase();
// #endif

    Circle circle;
    initCircle(30, &circle);
    printCircle(&circle);



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

    long double timeWithoutTransp = runOnTests(&tester, matricesMultiplyStandart);
    long double timeWithTransp    = runOnTests(&tester, matricesMultiplyWithTranspon);
    long double meanArifmWithout  = timeWithoutTransp / cntOfTests;
    long double meanArifmWith     = timeWithTransp / cntOfTests;

    printf("mean arifmetic time per test without transp: %.10Lg\n", meanArifmWithout);
    printf("mean arifmetic time per test with    transp: %.10Lg\n", meanArifmWith);
    destructTester(&tester);
}

void classShowcase() {
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

    // ------------------------------       MATRIX MULT     ---------------------------------------

    Matrix addResult = {};
    matrixInit(matrix.h, matrix.w, &addResult);
    matricesAdd(&matrix, &matrix, &addResult);
    printf("\n\n addition result matrix:\n");
    matrixPrint(&addResult);

    // ------------------------------       MATRIX ADD     ---------------------------------------

    Matrix multResult = {};
    getMatrixMultipilcationSizes(&matrix, &matrix_2, &multResult.h, &multResult.w);
    matrixInit(multResult.h, multResult.w, &multResult);
    matricesMultiply(&matrix, &matrix_2, &multResult, NO_TRANSPONATION);
    printf("\n\n multiplication result matrix:\n");
    matrixPrint(&multResult);
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
