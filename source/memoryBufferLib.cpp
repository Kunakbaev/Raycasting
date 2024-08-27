#include <stdlib.h>
#include <assert.h>

#include "../include/memoryBufferLib.hpp"
#include "../include/matrixLib.hpp"

const int MEM_SIZE = 1e3 + 10;

// memory allocated on heap
MatrixElem buffer[MEM_SIZE];
MatrixElem* bufferPtr = buffer;

void allocateMemory(Matrix* matrix) {
    assert(matrix != NULL);
    assert(matrix->h > 0);
    assert(matrix->w > 0);

    int need = matrix->h * matrix->w;
    assert(bufferPtr - buffer + need - 1 <= MEM_SIZE);
    matrix->data = (MatrixElem*)buffer;
    bufferPtr += need;
}

void freeMemory(Matrix* matrix) {
    assert(matrix       != NULL);
    assert(matrix->data != NULL);
    assert(matrix->h > 0);
    assert(matrix->w > 0);

    int need = matrix->h * matrix->w;
    bufferPtr -= need;
    matrix->data = NULL;
}
