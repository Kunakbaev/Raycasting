#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../include/circleLib.hpp"

const int MAX_RADIUS = 40;
const long double WIDTH_KOEF = 1;

static int sq(int x) {
    return x * x;
}

static void printMultipliedChar(char ch, int reps) {
    assert(reps >= 0);
    while (reps--)
        putchar(ch);
}

static int getRowWidth(int radius, int y) {
    assert(y <= radius);

    long double half = sqrtl(sq(radius) - sq(y));
    half *= WIDTH_KOEF;

    return int(half * 2);
}

void initCircle(int radius, Circle* circle) {
    assert(circle != NULL);
    assert(radius > 0);
    assert(radius <= MAX_RADIUS);

    circle->radius = radius;
    int arrLen = getArrLen(circle);
    circle->matrix    = (int*)calloc(arrLen, sizeof(int));
    circle->rowsSizes = (int*)calloc(arrLen, sizeof(int));
    circle->strides   = (int*)calloc(arrLen, sizeof(int));
    assert(circle->matrix    != NULL);
    assert(circle->rowsSizes != NULL);
    assert(circle->strides   != NULL);

    for (int i = 0; i < arrLen; ++i) {
        int y = abs(i - radius);
        int width = getRowWidth(radius, y) + 1;
        if (width > arrLen)
            width = arrLen;

        circle->rowsSizes[i] = width;
        printf("i : %d, y : %d, width: %d\n", i, y, width);
        if (!i)
            circle->strides[i] = 0;
        else
            circle->strides[i] = circle->strides[i - 1] + circle->rowsSizes[i - 1];
    }
}

int getArrLen(const Circle* circle) {
    assert(circle != NULL);

    // zosko vipendrilsya
    return circle->radius << 1 | 1;
}

void printCircle(const Circle* circle) {
    assert(circle != NULL);

    // also it's diametre of circle
    int arrLen = getArrLen(circle);
    for (int i = 0; i < arrLen; ++i) {
        int width = circle->rowsSizes[i];
        int bef = (arrLen - width) >> 1;
        printMultipliedChar(' ', bef);
        printMultipliedChar('@', width);
        printMultipliedChar(' ', bef);
        putchar('\n');
    }
}

/*

cd Documents
cd Work
cd Raycasting
make run

*/

