#ifndef CIRCLE_LIB
#define CIRCLE_LIB

struct Circle {
    int radius;
    int* rowsSizes;
    char* matrix;
    int* strides;
};

void clearScreen();
void initCircle(int radius, Circle* circle, int dx, int dy);
int getArrLen(const Circle* circle);
void printCircle(const Circle* circle);

#endif
