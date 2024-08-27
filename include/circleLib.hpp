#ifndef CIRCLE_LIB
#define CIRCLE_LIB

struct Circle {
    int radius;
    int* rowsSizes;
    int* matrix;
    int* strides;
};

void initCircle(int radius, Circle* circle);
int getArrLen(const Circle* circle);
void printCircle(const Circle* circle);

#endif
