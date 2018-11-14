
#include "ColItr.h"


ColItr::ColItr(Matrix& originalMatrix,int col) : matrixref(originalMatrix), col(0) {

}


//advance to next col
ColItr& ColItr::operator++(){
    col++;
    return (*this);
} // pre
ColItr& ColItr::operator++(int){
    return ++ (*this);
    if (col > matrixref.numCols){

    }

} // post

//move to prior col
ColItr& ColItr::operator--(){
    col--;
    return *this;
}// pre
ColItr& ColItr::operator--(int){
    return -- (*this);
} // post

ColItr& ColItr::operator+=(const int& rhs){
    col += rhs;
    return (*this);
} //advance self rhs cols
ColItr ColItr::operator+(const int& rhs){
    ColItr copy(*this);
    return copy+= rhs;
} //new iterator rhs cols past self

ColItr& ColItr::operator-=(const int& rhs){
    col -= rhs;
    return (*this);
} //move self back rhs cols
ColItr ColItr::operator-(const int& rhs){
    ColItr copy(*this);
    return copy -= rhs;
}

ColElementItr ColItr::operator*() {
    return ColElementItr();
}

ColItr::operator bool() const {
    return col >= 0 && col< matrixref.numCols;
}

bool ColItr::operator!() const {
    return !static_cast<bool>(*this);
}

bool ColItr::operator==(const ColItr &rhs) const {
    if (&matrixref != &rhs.matrixref){
        return false;
    }
    else if (*this && !rhs){
        return true;
    }
    else{
        return col == rhs.col;
    }
}

bool ColItr::operator!=(const ColItr &rhs) const {
    return !(*this == rhs);
}

bool ColItr::operator<(const ColItr &rhs) const {
    if (&matrixref != &rhs.matrixref){
        return false;
    }
    else if (*this && !rhs){
        return true;
    }
    else{
        return col < rhs.col;
    }
}

bool ColItr::operator>(const ColItr &rhs) const {
    if (&matrixref != &rhs.matrixref){
        return false;
    }
    else if (*this && !rhs){
        return true;
    }
    else{
        return col > rhs.col;
    }
}

bool ColItr::operator<=(const ColItr &rhs) const {
    return *this == rhs || *this < rhs;
}

bool ColItr::operator>=(const ColItr &rhs) const {
    return *this == rhs || *this > rhs;
}

double &ColItr::operator[](int i) {
    return matrixref[i];
}
//new iterator rhs cols before self
