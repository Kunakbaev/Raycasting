#ifndef MATRIX_LIB
#define MATRIX_LIB

typedef int MatrixElem;

struct Matrix {
    size_t h, w;
    MatrixElem* data;
};

enum MatrixMultiplicationAlgo {
    NO_TRANSPONATION,
    WIHT_TRANSPONATION,
};

enum MatrixDetermineAlgo {
    SUPER_SLOW,
    CUBIC,
};

void matrixInit(size_t h, size_t w, Matrix* matrix);
void matrixCopy(const Matrix* const src, Matrix* dest);
void matrixRead(Matrix* matrix);
void matrixSwapRows(Matrix* matrix, size_t row1, size_t row2);
MatrixElem* matrixGetRow(const Matrix* matrix, size_t row);
void matrixPrint(const Matrix* matrix);
void matrixTranspon(const Matrix* src, Matrix* dest);
void matricesAdd(const Matrix* one, const Matrix* two, Matrix* res);
void matricesMultiplyWithTranspon(const Matrix* one, const Matrix* two, Matrix* res);
void matricesMultiplyStandart(const Matrix* one, const Matrix* two, Matrix* res);
void matricesMultiply(const Matrix* one, const Matrix* two, Matrix* res, MatrixMultiplicationAlgo algo);
void getMatrixMultipilcationSizes(const Matrix* one, const Matrix* two, size_t* rows, size_t* cols);
size_t getMatrixElemIndex(const Matrix* matrix, size_t row, size_t col);
MatrixElem getDetermineSuperSlow(const Matrix* matrix);
MatrixElem getDetermineNcube(const Matrix* const matrix);
MatrixElem getDetermine(const Matrix* matrix, MatrixDetermineAlgo algo);

#endif

