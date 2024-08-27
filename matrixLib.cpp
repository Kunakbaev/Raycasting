#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrixLib.hpp"


void initMatrix(int h, int w, Matrix* matrix) {
    assert(matrix != NULL);
    assert(h >= 1);
    assert(w >= 1);

    matrix->h = h;
    matrix->w = w;
    matrix->data = (int*)calloc(w * h, sizeof(int));
}

void readMatrix(Matrix* matrix) {
    assert(matrix != NULL);

    printf("Please print your matrix:\n");
    for (int i = 0; i < matrix->h; ++i)
        for (int j = 0; j < matrix->w; ++j) {
            int elemInd = i * matrix->w + j;
            scanf("%d", &matrix->data[elemInd]);
        }
}

void printMatrix(const Matrix* matrix) {
    assert(matrix != NULL);

    const char* delims = ",";
    printf("{\n");
    for (int i = 0; i < matrix->h; ++i) {
        printf("    { ");
        for (int j = 0; j < matrix->w; ++j) {
            int elemInd = i * matrix->w + j;
            printf("%d", matrix->data[elemInd]);
            if (j != matrix->w - 1)
                printf(",");
            printf(" ");
        }
        printf("}\n");
    }
    printf("}\n");
}

void transponMatrix(const Matrix* src, Matrix* dest) {
    assert(src  != NULL);
    assert(dest != NULL);

    initMatrix(src->w, src->h, dest);
    for (int i = 0; i < src->h; ++i)
        for (int j = 0; j < src->w; ++j) {
            int srcInd  = i * src->w  + j;
            int destInd = j * dest->w + i;
            dest->data[destInd] = src->data[srcInd];
        }
}

static MatrixElem getScalarMult(const MatrixElem* one, const MatrixElem* two, size_t arrLen) {
    assert(one != NULL);
    assert(two != NULL);
    assert(arrLen > 0);

    MatrixElem result = 0;
    for (size_t i = 0; i < arrLen; ++i) {
        // be carefull with overflow
        result += one[i] * two[i];
    }
    return result;
}

void multiplyMatrixes(const Matrix* one, const Matrix* two, Matrix* res) {
    assert(one != NULL);
    assert(two != NULL);
    assert(res != NULL);
    assert(one->w == two->h);

    Matrix transp = {};
    transponMatrix(two, &transp);

    initMatrix(one->h, two->w, res);
    for (int i = 0; i < one->h; ++i) {
        const MatrixElem* oneRow = one->data + i * one->w;
        for (int j = 0; j < transp.h; ++j) {
            // be carefull with overflow
            const MatrixElem* transpRow = transp.data + j * transp.w;
            MatrixElem scalar = getScalarMult(oneRow, transpRow, one->w);
            int elemInd = i * res->w + j;
            res->data[elemInd] = scalar;
        }
    }
}
