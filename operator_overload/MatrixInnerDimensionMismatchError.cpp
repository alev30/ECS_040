#include <sstream>
#include "MatrixInnerDimensionMismatchError.h"
#include "Matrix.h"


MatrixInnerDimensionMismatchError::MatrixInnerDimensionMismatchError(const Matrix &ref1, const Matrix &ref2) : MatrixError(ref1,ref2) {
    std::stringstream errorStream;
    errorStream << "Inner dimensions do not agree. First matrix has " << ref1.getNumCols() <<  "columns but second matrix has " <<  ref2.getNumRows() << " rows." <<std::endl;
    errString = errorStream.str();

}

