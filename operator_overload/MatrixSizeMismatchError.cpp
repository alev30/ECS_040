#include <stdexcept>
#include <sstream>
#include "MatrixSizeMismatchError.h"
MatrixSizeMismatchError::MatrixSizeMismatchError (const Matrix &ref1,const Matrix &ref2) : MatrixError(ref1,ref2) {
    std::stringstream errorStream;
    errorStream << "Matrices must be the same size but Matrix1 is " << ref1.getNumRows() << " X " << ref1.getNumCols() <<  " but Matrix 2 is " << ref2.getNumRows() << " X " << ref2.getNumCols() << std::endl;
    errString = errorStream.str();
}
