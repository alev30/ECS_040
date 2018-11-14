#include "RowItr.h"






RowItr::RowItr(Matrix& passedMatrix, int row): matrixref(passedMatrix), row(0){

}

//advance to next row
RowItr& RowItr::operator++(){
    row++;
    return (*this);
} // pre
RowItr& RowItr::operator++(int){
    return ++ (*this);
    if (row > matrixref.numRows){

    }

} // post

//move to prior row
RowItr& RowItr::operator--(){
    row--;
    return *this;
}// pre
RowItr& RowItr::operator--(int){
    return -- (*this);
} // post

RowItr& RowItr::operator+=(const int& rhs){
    row += rhs;
    return (*this);
} //advance self rhs rows
RowItr RowItr::operator+(const int& rhs){
    RowItr copy(*this);
    return copy+= rhs;
} //new iterator rhs rows past self

RowItr& RowItr::operator-=(const int& rhs){
    row -= rhs;
    return (*this);
} //move self back rhs rows
RowItr RowItr::operator-(const int& rhs){
    RowItr copy(*this);
    return copy -= rhs;
}

RowElementItr RowItr::operator*() {
    return RowElementItr();
}

RowItr::operator bool() const {
    return row >= 0 && row< matrixref.numRows;
}

bool RowItr::operator!() const {
    return !static_cast<bool>(*this);
}

bool RowItr::operator==(const RowItr &rhs) const {
    if (&matrixref != &rhs.matrixref){
        return false;
    }
    else if (*this && !rhs){
        return true;
    }
    else{
        return row == rhs.row;
    }
}

bool RowItr::operator!=(const RowItr &rhs) const {
    return !(*this == rhs);
}

bool RowItr::operator<(const RowItr &rhs) const {
    if (&matrixref != &rhs.matrixref){
        return false;
    }
    else if (*this && !rhs){
        return true;
    }
    else{
        return row < rhs.row;
    }
}

bool RowItr::operator>(const RowItr &rhs) const {
    if (&matrixref != &rhs.matrixref){
        return false;
    }
    else if (*this && !rhs){
        return true;
    }
    else{
        return row > rhs.row;
    }
}

bool RowItr::operator<=(const RowItr &rhs) const {
    return *this == rhs || *this < rhs;
}

bool RowItr::operator>=(const RowItr &rhs) const {
    return *this == rhs || *this > rhs;
}

double &RowItr::operator[](int i) {

}
//new iterator rhs rows before self

