typedef int MatrixElem;

struct Matrix {
    size_t h, w;
    MatrixElem* data;
};

void initMatrix(int h, int w, Matrix* matrix);
void readMatrix(Matrix* matrix);
void printMatrix(const Matrix* matrix);
void transponMatrix(const Matrix* src, Matrix* dest);
void multiplyMatrixes(const Matrix* one, const Matrix* two, Matrix* res);

