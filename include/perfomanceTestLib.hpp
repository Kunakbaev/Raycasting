#ifndef PERFOMANCE_TEST_LIB
#define PERFOMANCE_TEST_LIB

#include "matrixLib.hpp"

struct Randomizer {

}

struct Test {
    Matrix one;
    Matrix two;
};

struct Tester {
    int cntOfTests;
    Test* tests;
};

typedef void (*funcPtr)(const Matrix* one, const Matrix* two, Matrix* res);

void generateTests(Tester* tester, int numOfTests);
void runOnTest(const Test* test, funcPtr solver, int testInd);
long double runOnTests(const Tester* tester, funcPtr solver);

#endif
