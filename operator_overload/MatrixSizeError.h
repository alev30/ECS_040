//
// Created by mfbut on 3/2/2018.
//

#ifndef MATRIX_MATRIXSIZEERROR_H
#define MATRIX_MATRIXSIZEERROR_H
#include "Matrix.h"
#include "MatrixError.h"

class MatrixSizeError : public MatrixError{
public:
    MatrixSizeError(const Matrix &ref1,const Matrix& ref2, int rowReq, int badRowElem);

private:
    int rowreq;
    int badrowelem;
};

#endif //MATRIX_MATRIXSIZEERROR_H
