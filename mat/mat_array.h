//
// Created by yourenchun on 2/8/18.
//

#ifndef MAT_MAT_H
#define MAT_MAT_H

#define MATTEMPLATE template<typename T>

#include <iostream>

enum INITTYPE {
    NONE,
    ZEROS,
    ONES,
    RANDOM
};

MATTEMPLATE
class Mat {
private:
    int cols;
    int rows;
    T **data;

public:
    Mat(int rows, int cols, INITTYPE type = NONE);

    ~Mat();

    void print();

    T *operator[](int i);
    T* operator[](int i) const;

    Mat<T>* operator+(const Mat<T> &A);

    // TODO: const pointer ?
//	const T* Mat<T>::operator[](int i) const;
};


MATTEMPLATE
Mat<T>::Mat(int rows, int cols, INITTYPE type) {
    this->rows = rows;
    this->cols = cols;
    // allocate memory
    this->data = new T *[this->rows];// create pointer array
    for (int i = 0; i < rows; i++) {
        this->data[i] = new T[this->cols];
    }

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (type == ZEROS) {
                this->data[i][j] = 0;
            } else if (type == ONES) {
                this->data[i][j] = 1;
            } else if (type == RANDOM) {
                //TODO
            }
        }
    }
}

MATTEMPLATE
void Mat<T>::print() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            std::cout << this->data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

MATTEMPLATE
Mat<T>::~Mat() {
    for (int i = 0; i < this->rows; i++) {
        delete[](this->data[i]);
    }
}

MATTEMPLATE
T *Mat<T>::operator[](int i) {
    return this->data[i];
}

// const instance can only call const function member.
MATTEMPLATE
T* Mat<T>::operator[](int i) const {
	return this->data[i];
}

MATTEMPLATE
Mat<T>* Mat<T>::operator+(const Mat<T> &A) {
    Mat<T> *B=new Mat(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            (*B)[i][j] = A[i][j] + (*this)[i][j];
            std::cout<<(*B)[i][j]<<std::endl;
        }
    }
    return B;
}

#endif //MAT_MAT_H
