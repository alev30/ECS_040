//
// Created by mfbut on 3/1/2018.
//

#ifndef MATRIX_MATRIXERROR_H
#define MATRIX_MATRIXERROR_H

#include <exception>
#include <string>
#include "Matrix.h"

class MatrixError : std::exception  {
 protected:
    MatrixError(const Matrix & matrixref1, const Matrix & matrixref2);
 private:
  virtual const char* what() const noexcept override;
 protected:
  std::string errString;
};

#endif //MATRIX_MATRIXERROR_H
