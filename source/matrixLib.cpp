#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/matrixLib.hpp"

void matrixInit(size_t h, size_t w, Matrix* matrix) {
    assert(matrix != NULL);
    assert(h >= 1);
    assert(w >= 1);

    matrix->h = h;
    matrix->w = w;
    size_t need = matrix->h * matrix->w;
    matrix->data = (MatrixElem*)calloc(need, sizeof(MatrixElem));
}

void matrixRead(Matrix* matrix) {
    assert(matrix       != NULL);
    assert(matrix->data != NULL);

    printf("Please print your matrix:\n");
    for (size_t i = 0; i < matrix->h; ++i)
        for (size_t j = 0; j < matrix->w; ++j) {
            size_t elemInd = getMatrixElemIndex(matrix, i, j);
            scanf("%d", &matrix->data[elemInd]);
        }
}

void matrixPrint(const Matrix* matrix) {
    assert(matrix       != NULL);
    assert(matrix->data != NULL);

    printf("{\n");
    for (size_t i = 0; i < matrix->h; ++i) {
        printf("    { ");
        for (size_t j = 0; j < matrix->w; ++j) {
            size_t elemInd = getMatrixElemIndex(matrix, i, j);
            printf("%d", matrix->data[elemInd]);
            if (j != matrix->w - 1)
                printf(",");
            printf(" ");
        }
        printf("}\n");
    }
    printf("}\n");
}

void matrixTranspon(const Matrix* src, Matrix* dest) {
    assert(src        != NULL);
    assert(dest       != NULL);
    assert(src->data  != NULL);
    assert(dest->data != NULL);

    for (size_t i = 0; i < src->h; ++i)
        for (size_t j = 0; j < src->w; ++j) {
            size_t srcInd  = getMatrixElemIndex(src,  i, j);
            size_t destInd = getMatrixElemIndex(dest, j, i);
            dest->data[destInd] = src->data[srcInd];
        }
}

static MatrixElem getScalarMult(const MatrixElem* one, const MatrixElem* two, size_t arrLen) {
    assert(one != NULL);
    assert(two != NULL);
    assert(arrLen > 0);

    MatrixElem result = 0;
    size_t i = 0;
    // vectorised for
    for (; i + 4 - 1 < arrLen; i += 4) {
        // be carefull with overflow
        result += one[i + 0] * two[i + 0];
        result += one[i + 1] * two[i + 1];
        result += one[i + 2] * two[i + 2];
        result += one[i + 3] * two[i + 3];
    }
    for (; i < arrLen; ++i) {
        // be carefull with overflow
        result += one[i] * two[i];
    }
    return result;
}

MatrixElem* matrixGetRow(const Matrix* matrix, size_t row) {
    assert(matrix != NULL);
    assert(matrix->data != NULL);
    // assert(0 <= row);
    assert(row < matrix->h);

    return matrix->data + row * matrix->w;
}

size_t getMatrixElemIndex(const Matrix* matrix, size_t row, size_t col) {
    assert(matrix != NULL);
    // assert(0 <= row);
    assert(row < matrix->h);
    // assert(0 <= col);
    assert(col < matrix->w);

    return row * matrix->w + col;
}

void matricesAdd(const Matrix* one, const Matrix* two, Matrix* res) {
    assert(one       != NULL);
    assert(two       != NULL);
    assert(res       != NULL);
    assert(one->w    == two->w);
    assert(one->h    == two->h);
    assert(one->data != NULL);
    assert(two->data != NULL);

    for (size_t i = 0; i < res->h; ++i) {
        for (size_t j = 0; j < res->w; ++j) {
            size_t oneInd = getMatrixElemIndex(one, i, j);
            size_t twoInd = getMatrixElemIndex(two, i, j);
            size_t resInd = getMatrixElemIndex(res, i, j);

            // be carefull with overflow
            res->data[resInd] = one->data[oneInd] + two->data[twoInd];
        }
    }
}

// GetMatrixElem(row, col);
// GetMatrixRow(row);
// Передавай enum, MatrixMultiplicationAlgo
// WorkspaceInit(MatrixMultiplicationAlgo);
// WorkspaceDtor
// GetMatrixMultipilcationSizes

void matricesMultiplyWithTranspon(const Matrix* one, const Matrix* two, Matrix* res) {
    assert(one       != NULL);
    assert(two       != NULL);
    assert(res       != NULL);
    assert(one->w    == two->h);
    assert(one->data != NULL);
    assert(two->data != NULL);
    assert(res->h    == one->h);
    assert(res->w    == two->w);

    Matrix transp = {}; // matrix на стеке громкое заявление
    matrixInit(two->w, two->h, &transp);
    matrixTranspon(two, &transp);
    for (size_t i = 0; i < one->h; ++i) {
        const MatrixElem* oneRow = matrixGetRow(one, i);
        for (size_t j = 0; j < transp.h; ++j) {
            // be carefull with overflow
            const MatrixElem* transpRow = matrixGetRow(&transp, j);
            MatrixElem scalar = getScalarMult(oneRow, transpRow, one->w);
            size_t elemInd = getMatrixElemIndex(res, i, j);
            res->data[elemInd] = scalar;
        }
    }
}

void matricesMultiplyStandart(const Matrix* one, const Matrix* two, Matrix* res) {
    assert(one       != NULL);
    assert(two       != NULL);
    assert(res       != NULL);
    assert(one->w    == two->h);
    assert(one->data != NULL);
    assert(two->data != NULL);

    for (size_t i = 0; i < one->h; ++i) {
        for (size_t j = 0; j < two->w; ++j) {
            MatrixElem scalar = 0;
            for (size_t e = 0; e < two->h; ++e) {
                size_t oneInd = getMatrixElemIndex(one, i, e);
                size_t twoInd = getMatrixElemIndex(two, e, j);

                // be carefull with overflow
                scalar += one->data[oneInd] * two->data[twoInd];
            }

            size_t resInd = getMatrixElemIndex(res, i, j);
            res->data[resInd] = scalar;
        }
    }
}

void getMatrixMultipilcationSizes(const Matrix* one, const Matrix* two, size_t* rows, size_t* cols) {
    assert(one  != NULL);
    assert(two  != NULL);
    assert(rows != NULL);
    assert(cols != NULL);

    *rows = one->h;
    *cols = two->w;
}

void matricesMultiply(const Matrix* one, const Matrix* two, Matrix* res, MatrixMultiplicationAlgo algo) {
    assert(one       != NULL);
    assert(two       != NULL);
    assert(res       != NULL);
    assert(one->w    == two->h);
    assert(one->data != NULL);
    assert(two->data != NULL);

    if (algo == NO_TRANSPONATION) {
        matricesMultiplyStandart(one, two, res);
    } else {
        matricesMultiplyWithTranspon(one, two, res);
    }
}
