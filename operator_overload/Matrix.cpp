#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iterator>
#include <list>
#include <assert.h>
#include "Matrix.h"
#include "MatrixSizeError.h"
#include "MatrixSizeMismatchError.h"
#include "MatrixInnerDimensionMismatchError.h"


Matrix::Matrix() {      //default constructor

}

Matrix::Matrix(const std::vector<std::vector<double>> &mat) : our_matrix(mat) {//explicit constructor
    std::vector<int> numcols;
    numcols.push_back((short)mat[0].size());

    numRows = (short) mat.size();
    numCols = (short)mat[0].size();

    Matrix tempMat = (*this);



    for (int i = 1; i < (short)mat.size(); i++){
        numcols.push_back((short)mat[i].size());
        if (numcols[i-1]!= numcols[i]){
            throw MatrixSizeError(tempMat, tempMat, numcols[i-1], numcols[i]);
        }
    }

}

Matrix::Matrix(const double val, const int numRows, const int numCols) {
    this->numRows = numRows;
    this->numCols = numCols;
    our_matrix.resize((unsigned long)numRows);
    for (int i = 0; i < numRows; i++){
        our_matrix[i].resize((unsigned long)numCols);
        for (int j = 0; j < numCols; j++){
            our_matrix[i][j] = val;
        }
    }
}

Matrix::Matrix(const Matrix &rhs) :
        our_matrix(rhs.our_matrix), valOfElement(rhs.valOfElement), numRows(rhs.numRows), numCols(rhs.numCols) {
}


int Matrix::getNumRows() const {
    return numRows;
}

int Matrix::getNumCols() const {
    return numCols;
}

/*std::vector<std::vector<double> > Matrix::getMatrix() const {
    return our_matrix;
}*/

/*RowItr Matrix::operator [](int i) {
    //return matrix[i];
}*/

//instream and outstream operator friend functions
std::ostream &operator<<(std::ostream &out, Matrix &matrix) {

    /*for (int i = 0; i < matrix.size(); ++i) {
    out << matrix.i << std::endl
    }*/
    /*for (int i = 0; i < matrix.getNumRows(); ++i) {
        for (int j = 0; j < matrix.getNumCols(); ++j) {
            std::cout << matrix.our_matrix[i][j] << " ";
        }
    std::cout << std::endl;
    }*/


    for (const auto &itr1 : matrix.our_matrix) {
        for (const auto &itr2 : itr1) {
            out << itr2 << " ";
        }
        out << std::endl;
    }

    return out;
}

std::istream &operator>>(std::istream &in, Matrix &matrix) {

    in >> matrix.numRows >> matrix.numCols;

    //in >> matrix.numCols;

    /*for (const auto& itr1 : matrix.our_matrix) {
        for (const auto& itr2 : itr1) {
            in >> itr2;
        }

    }*/
    for (int i = 0; i < matrix.numRows; i++) {
        std::vector<double> temp_Vec;
        double temp_Double;
        for (int j = 0; j < matrix.numCols; j++) {
            in >> temp_Double;
            //in >> matrix.our_matrix[i][j];
            temp_Vec.push_back(temp_Double);
        }
        matrix.our_matrix.push_back(temp_Vec);
    }

    return in;
}

Matrix Matrix::operator+(const double &rhs) const {
    Matrix new_matrix(this->our_matrix);

    for (int i = 0; (unsigned short) i < this->our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < this->our_matrix[i].size(); j++) {
            new_matrix.our_matrix[i][j] = this->our_matrix[i][j] + rhs;
        }
    }

    return new_matrix;
} // scalar addition

Matrix operator+(const double lhs, const Matrix &rhs) {
    MatrixSizeMismatchError echeck(*this, rhs);

    Matrix new_matrix1(rhs.our_matrix);

    for (int i = 0; (unsigned short) i < new_matrix1.our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < new_matrix1.our_matrix[i].size(); j++) {
            new_matrix1.our_matrix[i][j] = lhs + rhs.our_matrix[i][j];
        }
    }

    return new_matrix1;
} // scalar addition


Matrix &Matrix::operator+=(const double &rhs) {


    for (int i = 0; (unsigned short) i < this->our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < this->our_matrix[i].size(); j++) {
            this->our_matrix[i][j] += rhs;
        }
    }

    return *this;
} //scalar addition

Matrix Matrix::operator-(const double &rhs) const {

    Matrix new_matrix(this->our_matrix);

    for (int i = 0; (unsigned short) i < this->our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < this->our_matrix[i].size(); j++) {
            new_matrix.our_matrix[i][j] = this->our_matrix[i][j] - rhs;
        }
    }

    return new_matrix;

} // scalar subtraction

Matrix operator-(const double lhs, const Matrix &rhs) {

    MatrixSizeMismatchError echeck(*this, rhs);


    Matrix new_matrix1(rhs.our_matrix);
    int x = -1;
    for (int i = 0; (unsigned short) i < new_matrix1.our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < new_matrix1.our_matrix[i].size(); j++) {
            new_matrix1.our_matrix[i][j] = (lhs * x) + rhs.our_matrix[i][j];
        }
    }

    return new_matrix1;

} // scalar subtraction

Matrix &Matrix::operator-=(const double &rhs) {

    for (int i = 0; (unsigned short) i < this->our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < this->our_matrix[i].size(); j++) {
            this->our_matrix[i][j] -= rhs;
        }
    }

    return *this;

}// scalar subtraction


Matrix Matrix::operator*(const double &rhs) const {

    Matrix new_matrix(*this);

    for (int i = 0; (unsigned short) i < this->our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < this->our_matrix[i].size(); j++) {
            new_matrix.our_matrix[i][j] = this->our_matrix[i][j] * rhs;
        }
    }

    return new_matrix;

} // scalar multiplication

Matrix operator*(const double &lhs, const Matrix &rhs) {


    Matrix new_matrix1(rhs.our_matrix);
    for (int i = 0; (unsigned short) i < new_matrix1.our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < new_matrix1.our_matrix[i].size(); j++) {
            new_matrix1.our_matrix[i][j] = (lhs) * rhs.our_matrix[i][j];
        }
    }

    return new_matrix1;

} // scalar multiplication

Matrix &Matrix::operator*=(const double &rhs) {

    for (int i = 0; (unsigned short) i < this->our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < this->our_matrix[i].size(); j++) {
            this->our_matrix[i][j] *= rhs;
        }
    }

    return *this;

} // scalar multiplication



/*the following functions will define the matrix-matrix operations, (throw exceptions etc)*/

Matrix &Matrix::operator+=(const Matrix &rhs) {
    if (numRows != rhs.numRows || numCols != rhs.numCols) {
        throw MatrixSizeMismatchError(*this, rhs);

    }
    //throw EXCEPTION if matrices are not of the same size
    for (int i = 0; (unsigned short) i < this->our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < this->our_matrix[i].size(); j++) {
            this->our_matrix[i][j] += rhs.our_matrix[i][j];
        }
    }

    return *this;

} // matrix addition

Matrix Matrix::operator+(const Matrix &rhs) const {

    Matrix copy(*this);
    copy += rhs;
    return copy;


} // matrix addition


Matrix &Matrix::operator-=(const Matrix &rhs) {


    if (this->numRows != rhs.numRows || this->numCols!=rhs.numCols){
        throw  MatrixSizeMismatchError(*this, rhs);
    }

    //throw EXCEPTION if matrices are not of the same size
    for (int i = 0; (unsigned short) i < this->our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < this->our_matrix[i].size(); j++) {
            this->our_matrix[i][j] -= rhs.our_matrix[i][j];
        }
    }

    return *this;

} // matrix subtraction

Matrix Matrix::operator-(const Matrix &rhs) const {


    if (this->numRows != rhs.numRows || this->numCols!=rhs.numCols){
        throw  MatrixSizeMismatchError(*this, rhs);
    }


    //throw EXCEPTION if matrices are not the same
    Matrix new_matrix(this->our_matrix);

    for (int i = 0; (unsigned short) i < this->our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < this->our_matrix[i].size(); j++) {
            new_matrix.our_matrix[i][j] = this->our_matrix[i][j] - rhs.our_matrix[i][j];
        }
    }

    return new_matrix;

} //matrix subtraction


Matrix &Matrix::operator*=(const Matrix &rhs) {



    if(this->numCols!=rhs.numRows){
        throw MatrixInnerDimensionMismatchError(*this,rhs);
        // throw matrix inner dimension error //
    }

    //throw EXCEPTION if matrices are not of the same size
    /*for (int i = 0; (unsigned short) i < this->our_matrix.size(); i++) {
        for (int j = 0; (unsigned short) j < this->our_matrix[i].size(); j++) {
        this->our_matrix[i][j] *= rhs.our_matrix[i][j];
        //this->our_matrix[i][j]
        }
    }*/

    const int n = this->our_matrix.size();     // a rows
    const int m = this->our_matrix[0].size();  // a cols
    const int p = rhs.getNumCols();  // b cols

    //throw EXCEPTION if matrices are not the same
    //Matrix new_matrix(this->our_matrix);

    /*for (int i = 0; i < p; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                new_matrix.our_matrix[k][i] += this->our_matrix[k][j] * rhs.our_matrix[j][i];
            }
        }
    }*/

    int new_matrixRows = this->getNumRows();
    int new_matrixCols = rhs.getNumCols();
    Matrix new_matrix(std::vector<std::vector<double>>(new_matrixRows, std::vector<double>(new_matrixCols)));

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                new_matrix.our_matrix[k][i] += this->our_matrix[k][j] * rhs.our_matrix[j][i];
            }
        }
    }

    this->our_matrix = new_matrix.our_matrix;

    return *this;

} // matrix multiplication

Matrix Matrix::operator*(const Matrix &rhs) const {

    if(this->numCols!=rhs.numRows){
        throw MatrixInnerDimensionMismatchError(*this,rhs);
        // throw matrix inner dimension error //
    }



    const int n = this->our_matrix.size();     // a rows
    const int m = this->our_matrix[0].size();  // a cols
    const int p = rhs.getNumCols();  // b cols

    //throw EXCEPTION if matrices are not the same
    //Matrix new_matrix(this->our_matrix);

    /*for (int i = 0; i < p; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                new_matrix.our_matrix[k][i] += this->our_matrix[k][j] * rhs.our_matrix[j][i];
            }
        }
    }*/

    int new_matrixRows = this->getNumRows();
    int new_matrixCols = rhs.getNumCols();
    Matrix new_matrix(std::vector<std::vector<double>>(new_matrixRows, std::vector<double>(new_matrixCols)));

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                new_matrix.our_matrix[k][i] += this->our_matrix[k][j] * rhs.our_matrix[j][i];
            }
        }
    }


    return new_matrix;

} //matrix multiplication

