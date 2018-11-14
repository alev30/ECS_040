//
// Created by mfbut on 3/1/2018.
//

#include <sstream>
#include "MatrixError.h"

const char* MatrixError::what() const noexcept {
    return errString.c_str();
}

MatrixError::MatrixError(const Matrix &matrixref1, const Matrix &matrixref2) {
    std::stringstream errorStream;
    errorStream << matrixref1.getNumCols() << "holy balogne" << matrixref2.getNumRows() << std::endl;
    errString = errorStream.str();

}
