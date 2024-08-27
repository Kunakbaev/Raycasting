#ifndef PERFOMANCE_TEST_LIB
#define PERFOMANCE_TEST_LIB

#include "matrixLib.hpp"

// struct Randomizer {
//
// }

struct Randomizer {
    int numLowerBound;
    int numUpperBound;
    int widthLowerBound;
    int widthUpperBound;
    int heightLowerBound;
    int heightUpperBound;
};

struct Test {
    Matrix one;
    Matrix two;
};

struct Tester {
    int cntOfTests;
    Test* tests;
    Randomizer randomizer;
};

typedef void (*funcPtr)(const Matrix* one, const Matrix* two, Matrix* res);

void generateTests(Tester* tester, int numOfTests, const Randomizer* randomizer);
void runOnTest(const Test* test, funcPtr solver);
long double runOnTests(const Tester* tester, funcPtr solver);
void destructTester(Tester* tester);

#endif
