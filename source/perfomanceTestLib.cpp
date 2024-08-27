#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "perfomanceTestLib.hpp"
#include "matrixLib.hpp"

void generateTest(Test* test) {
    assert(test != NULL);
}

void generateTests(Tester* tester, int numOfTests) {
    assert(tester != NULL);

    tester->cntOfTests = numOfTests;
    tester->tests = (Test*)calloc(numOfTests, sizeof(Test));
    for (int i = 0; i < numOfTests; ++i) {

    }
}

void runOnTest(const Test* test, funcPtr solver, int testInd) {
    Matrix result;
    getMatrixMultipilcationSizes(&test->one, &test->two, &result.h, &result.w);
    matrixInit(result.h, result.w, &result);
    (*solver)(&test->one, &test->two, &result);
}

long double runOnTests(const Tester* tester, funcPtr solver) {
    clock_t startTime = clock();
    for (int i = 0; i < tester->cntOfTests; ++i) {
        runOnTest(&tester->tests[i], solver, i);
    }

    clock_t finishTime = clock();
    long double timeToCompute = (finishTime - startTime) / (long double)CLOCKS_PER_SEC;
    return timeToCompute;
}

void destructTester(Tester* tester) {
    assert(tester        != NULL);
    assert(tester->tests != NULL);

    free(tester->tests);
    tester->tests = NULL;
}
