CC=g++
CFLAGS= -std=c++14 -Wall -Werror -g
SOURCES= MainReadMatrixFromFile.cpp Matrix.cpp RowItr.cpp ColItr.cpp RowElementItr.cpp ColElementItr.cpp MatrixError.cpp MatrixSizeError.cpp MatrixSizeMismatchError.cpp MatrixInnerDimensionMismatchError.cpp
DEPS= Matrix.h RowItr.h ColItr.h RowElementItr.h ColElementItr.h MatrixError.h MatrixSizeError.h MatrixSizeMismatchError.h MatrixInnerDimensionMismatchError.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=matrix.out

all: matrix.out

matrix.out: MainReadMatrixFromFile.o Matrix.o RowItr.o ColItr.o RowElementItr.o ColElementItr.o MatrixError.o MatrixSizeError.o MatrixSizeMismatchError.o MatrixInnerDimensionMismatchError.o 
	g++ -g -std=c++14 -Wall -Werror -o matrix.out MainReadMatrixFromFile.o Matrix.o RowItr.o ColItr.o RowElementItr.o ColElementItr.o MatrixError.o MatrixSizeError.o MatrixSizeMismatchError.o MatrixInnerDimensionMismatchError.o 

MainReadMatrixFromFile.o: MainReadMatrixFromFile.cpp Matrix.h RowItr.h ColItr.h RowElementItr.h ColElementItr.h MatrixError.h MatrixSizeError.h MatrixSizeMismatchError.h MatrixInnerDimensionMismatchError.h  
	g++ -g -std=c++14 -Wall -Werror -c MainReadMatrixFromFile.cpp
    
Matrix.o: Matrix.h Matrix.cpp
	g++ -g -std=c++14 -Wall -Werror -c Matrix.cpp 

RowItr.o: RowItr.h RowItr.cpp
	g++ -g -std=c++14 -Wall -Werror -c RowItr.cpp

ColItr.o: ColItr.h ColItr.cpp 
	g++ -g -std=c++14 -Wall -Werror -c ColItr.cpp

RowElementItr.o: RowElementItr.h RowElementItr.cpp
	g++ -g -std=c++14 -Wall -Werror -c RowElementItr.cpp

ColElementItr.o: ColElementItr.h ColElementItr.cpp
	g++ -g -std=c++14 -Wall -Werror -c ColElementItr.cpp

MatrixError.o: MatrixError.h MatrixError.cpp
	g++ -g -std=c++14 -Wall -Werror -c MatrixError.cpp

MatrixSizeError.o: MatrixSizeError.h MatrixSizeError.cpp
	g++ -g -std=c++14 -Wall -Werror -c MatrixSizeError.cpp
	
MatrixSizeMismatchError.o: MatrixSizeMismatchError.h MatrixSizeMismatchError.cpp
	g++ -g -std=c++14 -Wall -Werror -c MatrixSizeMismatchError.cpp
	
MatrixInnerDimensionMismatchError.o: MatrixInnerDimensionMismatchError.h MatrixInnerDimensionMismatchError.cpp
	g++ -g -std=c++14 -Wall -Werror -c MatrixInnerDimensionMismatchError.cpp

clean: 
	-rm -f *.o* matrix.out 