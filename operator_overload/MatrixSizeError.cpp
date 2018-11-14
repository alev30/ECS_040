#include <sstream>
#include "MatrixSizeError.h"

MatrixSizeError::MatrixSizeError(const Matrix &ref1,const Matrix &ref2, int rowReq, int badRowElem) : MatrixError(ref1,ref2), rowreq(rowReq), badrowelem(badRowElem) {
    std::stringstream errorStream;
    errorStream << "All rows of the matrix should have the same number of elements. Expected rows to contain " << rowreq << " elements but found row that contained " << badrowelem << " elements." <<std::endl;
    errString = errorStream.str();

}
