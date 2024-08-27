#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../include/circleLib.hpp"

const int MAX_RADIUS = 40;
const long double WIDTH_KOEF = 0.5;

static int sq(int x) {
    return x * x;
}

static void printMultipliedChar(char ch, int reps) {
    assert(reps >= 0);
    while (reps--)
        putchar(ch);
}

long double max(long double a, long double b) {
    return a > b ? a : b;
}
static int getRowWidth(int radius, int y) {
    //assert(y <= radius);

    long double half = sqrtl(max(sq(radius) - sq(y * 2), 0.0));
    return int(half * 2);
}

void initCircle(int radius, Circle* circle) {
    assert(circle != NULL);
    assert(radius > 0);
    assert(radius <= MAX_RADIUS);

    circle->radius = radius;
    int arrLen = getArrLen(circle);
    circle->rowsSizes = (int*)calloc(arrLen / 2, sizeof(int));
    circle->strides   = (int*)calloc(arrLen / 2, sizeof(int));
    assert(circle->matrix    != NULL);
    assert(circle->rowsSizes != NULL);
    assert(circle->strides   != NULL);

    int sumLen = 0;
    for (int i = 0; i < arrLen / 2; ++i) {
        int y = abs(i + radius / 2 + 1 - radius);
        int width = getRowWidth(radius, y) + 1;
        if (width > arrLen)
            width = arrLen;

        circle->rowsSizes[i] = width;
        printf("i : %d, y : %d, width: %d\n", i, y, width);
        if (!i)
            circle->strides[i] = 0;
        else
            circle->strides[i] = circle->strides[i - 1] + circle->rowsSizes[i - 1] + 1; // \0 symbol
        sumLen += width;
    }

    circle->matrix = (char*)calloc(sumLen, sizeof(int));
    printf("sumLen : %d\n", sumLen);

    for (int i = 0; i < arrLen / 2; ++i) {
        int bef    = circle->strides[i];
        int rowLen = circle->rowsSizes[i];
        for (int j = 0; j < rowLen; ++j)
            *(circle->matrix + bef + j) = '0' + (j % 10);
        *(circle->matrix + bef + rowLen) = '\0';
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
    for (int i = 0; i < arrLen / 2; ++i) {
        int width = circle->rowsSizes[i];
        int bef = (arrLen - width) >> 1;
        printMultipliedChar(' ', bef);
        //printMultipliedChar('@', width);
        const char* s = circle->matrix + circle->strides[i];
        printf("%s", s);
        printMultipliedChar(' ', bef);
        putchar('\n');
    }

    printf("array : \n");
    for (int i = 0; i < arrLen / 2; ++i) {
        const char* s = circle->matrix + circle->strides[i];
        printf("%s\n", s);
    }
}

/*

cd Documents
cd Work
cd Raycasting
make run

*/

