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

void matrixInit(int h, int w, Matrix* matrix);
void matrixRead(Matrix* matrix);
MatrixElem* matrixGetRow(const Matrix* matrix, int row);
void matrixPrint(const Matrix* matrix);
void matrixTranspon(const Matrix* src, Matrix* dest);
void matricesAdd(const Matrix* one, const Matrix* two, Matrix* res);
void matricesMultiply(const Matrix* one, const Matrix* two, Matrix* res, MatrixMultiplicationAlgo algo);
void getMatrixMultipilcationSizes(const Matrix* one, const Matrix* two, size_t* rows, size_t* cols);

#endif

