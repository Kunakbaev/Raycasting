#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <random>

#include "../include/perfomanceTestLib.hpp"
#include "../include/matrixLib.hpp"

//    getRandInRange()
static int dice(int lower, int upper) {
    assert(lower <= upper);

    int len = upper - lower + 1;
    int num = lower + (rand() % len);
    return num;
}

static void generateMatrix(Matrix* matrix, size_t height, size_t width, const Randomizer* randomizer) {
    assert(matrix                    != NULL);
    assert(randomizer->numLowerBound < randomizer->numUpperBound);

    matrixInit(height, width, matrix);
    for (size_t i = 0; i < matrix->h; ++i)
        for (size_t j = 0; j < matrix->w; ++j) {
            //printf("i : %zu, j : %zu, height : %zu, width : %zu\n", i, j, height, width);
            size_t elemInd = getMatrixElemIndex(matrix, i, j);
            int num = dice(randomizer->numLowerBound, randomizer->numUpperBound);
            matrix->data[elemInd] = num;
        }
}

static void generateTest(Test* test, const Randomizer* randomizer) {
    assert(test                         != NULL);
    assert(randomizer->widthLowerBound  < randomizer->widthUpperBound);
    assert(randomizer->heightLowerBound < randomizer->heightUpperBound);

    size_t h1 = (size_t)dice(randomizer->heightLowerBound, randomizer->heightUpperBound);
    size_t w1 = (size_t)dice(randomizer->widthLowerBound, randomizer->widthUpperBound);
    size_t w2 = (size_t)dice(randomizer->widthLowerBound, randomizer->widthUpperBound);

    generateMatrix(&test->one, h1, w1, randomizer);
    generateMatrix(&test->two, w1, w2, randomizer);
}

void generateTests(Tester* tester, int numOfTests, const Randomizer* randomizer) {
    assert(tester     != NULL);
    assert(numOfTests > 0);

    srand(1ULL);
    tester->cntOfTests = numOfTests;
    tester->tests = (Test*)calloc((size_t)numOfTests, sizeof(Test));
    for (int i = 0; i < numOfTests; ++i)
        generateTest(&tester->tests[i], randomizer);
}

void runOnTest(const Test* test, funcPtr solver) {
    assert(test   != NULL);
    assert(solver != NULL);

    Matrix result = {};
    getMatrixMultipilcationSizes(&test->one, &test->two, &result.h, &result.w);
    matrixInit(result.h, result.w, &result);
    (*solver)(&test->one, &test->two, &result);
}

static long double sq(long double x) {
    return x * x;
}

long double runOnTests(const Tester* tester, funcPtr solver, long double* disp) {
    assert(tester        != NULL);
    assert(tester->tests != NULL);
    assert(solver        != NULL);
    assert(disp          != NULL);
    //assert(tester->cntOfTests > 0);


    long double mean = 0;
    *disp = 0;

    long double* runTimes = (long double*)calloc(tester->cntOfTests, sizeof(long double));
    assert(runTimes != NULL);
    for (int i = 0; i < tester->cntOfTests; ++i) {
        clock_t startTime = clock();
        runOnTest(&tester->tests[i], solver);
        clock_t finishTime = clock();
        long double timeToCompute = (long double)(finishTime - startTime) / CLOCKS_PER_SEC;

        mean += timeToCompute;
        runTimes[i] = timeToCompute;
    }

    mean /= tester->cntOfTests;
    for (int i = 0; i < tester->cntOfTests; ++i) {
        *disp += sq(runTimes[i] - mean);
    }
    *disp /= tester->cntOfTests;

    free(runTimes);
    return mean;
}

void destructTester(Tester* tester) {
    assert(tester        != NULL);
    assert(tester->tests != NULL);

    free(tester->tests);
    tester->tests = NULL;
}
