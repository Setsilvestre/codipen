#pragma once

using namespace std;
#include <exception>			//Management of exceptions
#include <iostream>				//Management of cin and cout
#include <stdlib.h>				//Management of random numbers: srand, rand 

/* 
* This class represent a two dimensional matrix of a general DataType
*/
template <class DataType>
class Matrix2D
{
	int x;
	int y;
	DataType * data;

public:
/*
* Overloaded constructor. It creates the matrix and set the values to random between 1 and 10
* @param x is the number of rows
* @param y is the number of columns
*/
Matrix2D(int x, int y) {
	if ((x <= 0) || (y <= 0)) {
		throw exception("Matrix with negative or null dimensions doesn't exist");
	}

	this->x = x;
	this->y = y;
	data = 0;
		//Allocate memory
	data = new DataType[x*y];
	if (data == 0) {
		throw exception("System was not able to create the matrix");
	}

		//Initialize the data to zero
	for (int i = 0; i < x*y; i++) {
		data[i] = 0;
	}
	
}

/* 
* Copy constructor
* @param m is the matrix to copy
*/
Matrix2D(const Matrix2D & m) {
	x = m.x;
	y = m.y;
	data = 0;
	//Allocate memory
	data = new DataType[x*y];
	if (data == 0) {
		throw exception("System was not able to create the matrix");
	}

	//Initialize the points to null. 
	for (int i = 0; i < x*y; i++) {
		data[i] = m.data[i];
	}
}

/*
* Destructor
*/
~Matrix2D() {
	if (data!=0) {
		delete[] data;
	}
}

int getRows() {
	return x;
}

int getColumns() {
	return y;
}

DataType& Get(int xPosition, int yPosition) {
	return data[xPosition * y + yPosition];
}

void Set(int xPosition, int yPosition, DataType value) {
	data[xPosition * y + yPosition] = value;
}

/*
* Resizes a matrix of x by y dimensions. Then, it randomly initializes the elements
* @param x is the x dimension
* @param y is the y dimension
*/
void ResizeMatrix(int x, int y, int row) {
		if ((x <= 0) || (y <= 0)) {
			throw exception("Matrix with negative or null dimensions doesn't exist");
		}
		//If the matrix contained data, we need to delete it to avoid memory leaks
		cout << "hola";
		system("pause");
		//Allocate memory
		int *newdata;
		newdata = new DataType[(x - 1)*y];
		if (newdata == 0) {
			throw exception("System was not able to create the matrix");
		}
		if (row != 0){
			for (int i = 0; i < (row)*y; i++) {
				newdata[i] = data[i];
			}
		}
		if (row != x){
			for (int i = (row + 1)*y; i < x*y; i++) {
				newdata[i] = data[i];
			}
		}
		delete[] data;
		this->x = x - 1;
		data = new DataType[(x)*y];
		for (int i = 0; i < x*y; i++) {
			data[i] = newdata[i];
		}
		delete[] newdata;
		
}

/*
* Adds m1 and m2 and it stores the result in the current object
* @param m1 is the matrix 1
* @param m2 is the matrix 2
*/
void SumMatrix(Matrix2D & m1, Matrix2D & m2) {
	if ((x == m1.x) && (m1.x == m2.x) && (y == m1.y) && (m1.y == m2.y)) {
		for (int i = 0; i < x*y; i++) {
			data[i] = m1.data[i] + m2.data[i];
		}
	}
	else {
		throw exception("Addition of matrix can only be done if all have the same dimensions");	
	}
}

/*
* + operators is overloaded to allow you to use cout directly with a Matrix2D object
* @param m2 is the matrix to add to the current matrix
* @param m3 is the new matrix
*/
Matrix2D operator+(const Matrix2D & m2) {
	Matrix2D matrixResult(x, y);

	if ((x == m2.x) && (y == m2.y)) {
		matrixResult.x = x;
		matrixResult.y = y;
		for (int i = 0; i < matrixResult.x*matrixResult.y; i++) {
			matrixResult.data[i] = data[i] + m2.data[i];
		}
	}
	else {
		throw exception("Addition of matrix can only be done if all have the same dimensions");
	}
	return matrixResult;
}


/*
* = operator is overloaded to allow you to work with the assignments used in the + operator
* @param m is the matrix to assign
* @return create a copy of the matrix and return it
*/
Matrix2D & operator=(const Matrix2D & m) {
	x = m.x;
	y = m.y;

	//Allocate memory
	data = new DataType[x*y];
	if (data == 0) {
		throw exception("System was not able to create the matrix");
	}

	//Initialize to zero
	for (int i = 0; i < x*y; i++) {
		data[i] = m.data[i];
	}

	
	return *this;
}

/*
* Output operators is overloaded to allow you to use cout directly with a Matrix2D object
* @param os is the output operator
* @param m is the matrix to show
*/
friend ostream& operator<<(ostream& os, const Matrix2D& m) {
	
	for (int i = 0; i < m.x*m.y; i++) {
		if (i % m.y == 0)
			os << endl;

		os << m.data[i] << "\t";
		
	}
	os << endl;
	return os;
}
};

