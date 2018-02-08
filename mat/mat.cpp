//
// Created by yourenchun on 2/8/18.
//
#include "mat.h"
MATTEMPLATE
Mat<T>::Mat(int rows, int cols, INITTYPE type = INITTYPE::ZEROS) {
	this->rows = rows;
	this->cols = cols;
	// allocate memory
	this->data = new T*[this->rows];// create pointer array
	for (int i = 0;i<rows;i++) {
		this->data[i] = new T[this->cols];
	}


	if (type == INITTYPE::ZEROS) {
		// init with zeros
		for (int i = 0;i<this->cols;i++) {
			for (int j = 0;j<this->rows;j++) {
				this->data[i][j] = 0;
			}
		}
	}
	else if (type == INITTYPE::ONES) {
		// init with ones
		for (int j = 0;j<this->rows;j++) {
			this->data[i][j] = 1;
		}
	}
}

MATTEMPLATE
Mat<T>::~Mat() {
	for (int i = 0;i < this->rows;i++) {
		delete[](this->data[i]);
	}
}

MATTEMPLATE
T* Mat<T>::operator[](int i) {
	return this->data[i];
}

const T* Mat<T>::operator[](int i) const {
	return this->data[i];
}

MATTEMPLATE
Mat<T> Mat<T>::operator+(const Mat<T> &A) {
	Mat<T> B(this->rows, this->cols);
	for (int i = 0;i < this->rows;i++) {
		for (int j = 0;j < this->cols;j++) {
			B[i][j] = A[i][j] + (*this)[i][j];
		}
	}
	return B;
}