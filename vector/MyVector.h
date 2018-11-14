//
// Created by mfbut on 3/10/2018.
//

#ifndef MYVECTOR_MYVECTOR_H
#define MYVECTOR_MYVECTOR_H

#include <sstream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <vector>
#include <ostream>
#include "ConstVectorItr.h"
#include "VectorItr.h"


template<typename T>
class MyVector;

//overloaded out for MyVector. Prints {element1 element2 element3 ...}
//you may choose to make this function a friend of MyVector if you want
template<typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>& myVector){
    for (int i = 0 ; i < myVector.elementSize; i++){
        out << *(myVector.valuelist[i].get()) << ' ';
    }
    out << std::endl;
    return out;
}


template<typename T>
class MyVector {
public:
    std::unique_ptr<T>* valuelist;
    unsigned int capacity;
    unsigned int elementSize;

  MyVector();
  explicit MyVector(const unsigned int& numElements); //create numElements empty items
  MyVector(const unsigned int& numElements, const T& value); // create numElements items all initialized to value
 
  //here I am templating this particular member method over another type U
  //this will allow us to convert things like a vector<vector<string>> to a 
  //MyVector<MyVector<string>> which wouldn't be possible othewise
  template <typename U>
  explicit MyVector(const std::vector<U>& values); // create a MyVector with the same values as standard vector
  MyVector(const MyVector& orig); // create a copy of a MyVector
  virtual ~MyVector(); //clean up any dynamically allocated space for a MyVector
  MyVector& operator=(const MyVector<T>& rhs); // make this MyVector have a COPY of all the values in rhs

  unsigned int size() const; // return the
  bool isEmpty() const; //return true if the vector has no elements in it

  T& front(); //return a reference the first element in MyVector
  const T& front() const; //return a const reference the first element in MyVector
  T& back(); //return a reference to the last element in MyVector
  const T& back() const; //return a const reference to the last element in MyVector
  T& at(const unsigned int& index); //return a reference to the element at the specified position
  const T& at(const unsigned int& index) const;  //return a const reference to the element at the specified position
  T& operator[](const unsigned int& index); //return a reference to the element at the specified position
  const T& operator[](const unsigned int& index) const; //return a const reference to the element at the specified position

  //insert a value into the vector at the specified position
  //for the iterator versions the position is wherever they are pointing at in the vector
  void insert(const unsigned int& pos, const T& value);
  void insert(const VectorItr<T>& itr, const T& value);
  void insert(const ConstVectorItr<T>& itr, const T& value);

  //remove a value from the vector at the specified position
  //for the iterator versions the position is wherever they are pointing at in the vector
  void erase(const unsigned int& pos);
  void erase(const VectorItr<T>& itr);
  void erase(const ConstVectorItr<T>& itr);

  void pushBack(const T& value); // add an element to the end of the vector
  void popBack(); // remove the last element from the vector

  void clear();// remove all the elements from the vector


  ConstVectorItr<T> begin() const;//get a constant iterator to the beginning of the vector
  ConstVectorItr<T> end() const; //get a constant iterator to the end of the vector

  VectorItr<T> begin(); //get a mutating iterator to the beginning of the vector
  VectorItr<T> end();  //get a mutating iterator to the beginning of the vector

  ConstVectorItr<T> cbegin() const;//get a constant iterator to the beginning of the vector
  ConstVectorItr<T> cend() const; //get a constant iterator to the end of the vector

};



//this is a nested template declaration. 
//this is the right way of doing things if you have a template show up inside another template
//I've given you this because we didn't cover it in class
//template<typename T>
//template <typename U>
//MyVector<T>::MyVector(const std::vector<U>& values) {

//}







template <typename T>
MyVector<T>::MyVector() : valuelist(nullptr), capacity(0), elementSize(0){}

template<typename T>
MyVector<T>::MyVector(const unsigned int &numElements) : capacity(numElements),elementSize(0) {

    // dynamically allocate space for array
    valuelist = new std::unique_ptr<T>[numElements];
    // new is like the * (array portion)
    for (int i  = 0; i <  numElements; ++ i){
        valuelist[i] = std::make_unique<T>(); // creates empty element at index I of type T
    }


    // empty element
    //values = std::make_unique<T>();
    // in order to get actual int value
    // int x = *(values[0].get());
}

template<typename T>
MyVector<T>::MyVector(const unsigned int &numElements, const T &value) : capacity(numElements),elementSize(numElements) {
    // dynamically allocate space for array
    valuelist = new std::unique_ptr<T>[numElements];
    // new is like the * (array portion)
    for (int i  = 0; i <  numElements; ++ i){
        valuelist[i] = std::make_unique<T>(value);
    }
}

template <typename T>
template <typename U>
MyVector<T>::MyVector(const std::vector<U> &values) : capacity((short)values.size()),elementSize((short)values.size()) {
    valuelist = new std::unique_ptr<T> [capacity];
    for (int i = 0; i < capacity; i++){
        valuelist[i] = std:: make_unique<T>(values[i]);
    }
}




template <typename T>
MyVector<T>::MyVector(const MyVector<T>& orig): capacity(orig.capacity){
    valuelist = new std ::unique_ptr<T> [capacity];
    elementSize = orig.elementSize;
    for (int i = 0; i < capacity; i++){
        valuelist[i] = std:: make_unique<T>(*(orig.valuelist[i].get()));
    }
}

template <typename T>
MyVector<T>::~MyVector() {}

template <typename T>
unsigned int MyVector<T>::size() const {
    return this->elementSize;
}

template <typename T>
bool MyVector<T>::isEmpty() const {
    if (this->elementSize == 0){
        return true;
    }
    else{
        return false;
    }
}


template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& rhs){
    MyVector<T> temp;
    temp.valuelist = new std::unique_ptr<T> [rhs.capacity];
    temp.elementSize = rhs.elementSize;
    for (int i = 0; i < temp.elementSize; i++){
        temp.valuelist[i] = std:: make_unique<T>(*(rhs.valuelist[i].get()));
    }

    return temp;
}


template<typename T>
T &MyVector<T>::front() {
    return *(valuelist[0].get());
}

template<typename T>
const T &MyVector<T>::front() const {
    return *(valuelist[0].get());
}

template<typename T>
T &MyVector<T>::back() {
    return *(valuelist[elementSize-1].get());
}

template<typename T>
const T &MyVector<T>::back() const {
    return *(valuelist[elementSize-1].get());
}

template<typename T>
T &MyVector<T>::at(const unsigned int &index) {
    return *(valuelist[index].get());
}

template<typename T>
const T &MyVector<T>::at(const unsigned int &index) const {
    return *(valuelist[index].get());
}

template<typename T>
T &MyVector<T>::operator[](const unsigned int &index) {
    return *(valuelist[index].get());
}

template<typename T>
const T &MyVector<T>::operator[](const unsigned int &index) const {
    return *(valuelist[index].get());
}

template<typename T>
void MyVector<T>::insert(const unsigned int &pos, const T &value) {
    elementSize++;
    capacity *=2;
    MyVector<T> temp;
    temp.elementSize = elementSize;
    temp.capacity = capacity;
    temp.valuelist = new std::unique_ptr<T> [capacity];
    for (unsigned int i = 0; i < pos; i++){
        temp.valuelist[i] = std:: make_unique<T>(*(valuelist[i].get()));
        std::cout <<*(valuelist[i].get()) <<  "test" <<  std::endl;
    }

    temp.valuelist[pos] = std::make_unique<T>(value);
    std:: cout << *(temp.valuelist[pos].get())  << "test" << std::endl;

    if ( pos < elementSize -1) {
        for (unsigned int i = pos + 1; i <= temp.elementSize; i++) {
            unsigned int j = pos;
            temp.valuelist[i] = std::make_unique<T>(*(valuelist[j].get()));
        }
    }

    //delete valuelist;

    valuelist = std::move(temp.valuelist);

   /* valuelist = new std::unique_ptr<T> [capacity];
    for (int i = 0; i < temp.elementSize; i++){
        valuelist[i] = std:: make_unique<T>(*(temp.valuelist[i].get()));
    }
*/
    //delete temp.valuelist;


}

template<typename T>
void MyVector<T>::insert(const VectorItr<T> &itr, const T &value) {

}

template<typename T>
void MyVector<T>::insert(const ConstVectorItr<T> &itr, const T &value) {

}

template<typename T>
void MyVector<T>::erase(const unsigned int &pos) {
    elementSize--;
    capacity--;
    MyVector<T> temp;
    temp.elementSize = elementSize;
    temp.capacity = capacity;
    temp.valuelist = new std::unique_ptr<T> [capacity];
    for (unsigned int i = 0; i < pos; i++){
        temp.valuelist[i] = std:: make_unique<T>(*(valuelist[i].get()));
    }
    for (unsigned int i = pos; i < temp.elementSize; i++){
        unsigned int j = pos+1;
        temp.valuelist[i] = std:: make_unique<T>(*(valuelist[j].get()));
    }

    delete valuelist;

    valuelist = new std::unique_ptr<T> [capacity];
    for (int i = 0; i < temp.elementSize; i++){
        valuelist[i] = std:: make_unique<T>(*(temp.valuelist[i].get()));
    }

    //delete temp.valuelist;
}

template<typename T>
void MyVector<T>::erase(const VectorItr<T> &itr) {

}

template<typename T>
void MyVector<T>::erase(const ConstVectorItr<T> &itr) {

}

template<typename T>
void MyVector<T>::pushBack(const T &value) {
    insert(elementSize-1,value);
}

template<typename T>
void MyVector<T>::popBack() {
    erase(elementSize-1);
}

template<typename T>
void MyVector<T>::clear() {
    delete valuelist;
}

template<typename T>
ConstVectorItr<T> MyVector<T>::begin() const {
    return ConstVectorItr<T>();
}

template<typename T>
ConstVectorItr<T> MyVector<T>::end() const {
    return ConstVectorItr<T>();
}

template<typename T>
VectorItr<T> MyVector<T>::begin() {
    return VectorItr<T>();
}

template<typename T>
VectorItr<T> MyVector<T>::end() {
    return VectorItr<T>();
}

template<typename T>
ConstVectorItr<T> MyVector<T>::cbegin() const {
    return ConstVectorItr<T>();
}

template<typename T>
ConstVectorItr<T> MyVector<T>::cend() const {
    return ConstVectorItr<T>();
}


#endif //MYVECTOR_MYVECTOR_H
