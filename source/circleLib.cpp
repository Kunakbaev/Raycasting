#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#include "../include/circleLib.hpp"

const int MAX_RADIUS = 60;
const long double WIDTH_KOEF = 0.5;

// static const char* brightnessChars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";
static const char* brightnessChars = "`.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

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

void initCircle(int radius, Circle* circle, int dx, int dy) {
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
        //printf("i : %d, y : %d, width: %d\n", i, y, width);
        if (!i)
            circle->strides[i] = 0;
        else
            circle->strides[i] = circle->strides[i - 1] + circle->rowsSizes[i - 1] + 1; // \0 symbol
        sumLen += width;
    }

    circle->matrix = (char*)calloc(sumLen, sizeof(int));
    // printf("sumLen : %d\n", sumLen);


    int centerI = -(radius / 2 + 1 - radius);
    int centerJ = radius + 1;
    centerI += dy;
    centerJ += dx;


    for (int i = 0; i < arrLen / 2; ++i) {
        int bef    = circle->strides[i];
        int rowLen = circle->rowsSizes[i];
        for (int j = 0; j < rowLen; ++j) {
            int dist = sqrtl(sq(i - centerI) + sq(j - centerJ));
            int maxDist = radius + sqrtl(sq(dx) + sq(dy));
            int ind = round((long double)(strlen(brightnessChars) * sqrtl((long double)dist)) /
                sqrtl((long double)maxDist));
            //int ind = round((long double)(strlen(brightnessChars) * dist)) / maxDist;
            if (ind >= strlen(brightnessChars))
                ind = strlen(brightnessChars) - 1;
            ind = strlen(brightnessChars) - ind - 1;

            *(circle->matrix + bef + j) = brightnessChars[ind];
        }
        *(circle->matrix + bef + rowLen) = '\0';
    }
}

int getArrLen(const Circle* circle) {
    assert(circle != NULL);

    // zosko vipendrilsya
    return circle->radius << 1 | 1;
}

void clearScreen() {
    system("clear");
    // const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    // write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void printCircle(const Circle* circle) {
    assert(circle != NULL);

    //printf("%s\n", brightnessChars);
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
//
//     printf("array : \n");
//     for (int i = 0; i < arrLen / 2; ++i) {
//         const char* s = circle->matrix + circle->strides[i];
//         printf("%s\n", s);
//     }
}

/*

cd Documents
cd Work
cd Raycasting
make run

*/

