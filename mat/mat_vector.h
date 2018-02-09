//
// Created by yourenchun on 2/8/18.
//

#ifndef MAT_MAT_H
#define MAT_MAT_H

#define MATTEMPLATE template<typename T>

#include <iostream>
#include <vector>

using std::vector;
enum INITTYPE {
    NONE,
    ZEROS,
    ONES,
    RANDOM
};

class span {
    static const std::string all;
public:
    int a;
    int b;
    span(int a, int b) {
        this->a=a;
        this->b=b;
    }
};

MATTEMPLATE
class Mat {
private:
    int cols;
    int rows;
    vector<vector<T>> data;

public:
    Mat();
    Mat(const Mat &A);//default constructor
    Mat(int rows, int cols, INITTYPE type = NONE);

    ~Mat();

    int getCols() const;
    int getRows() const;
    void print() const;
    Mat<T> matMul(const Mat<T> &A) const;
    Mat<T> subMat(span rows,span cols);

    const vector<T>& operator[](int i) const;

    vector<T>& operator[](int i);
    // element-wise + - * /
    Mat<T> operator+(const Mat<T> &A);
    Mat<T> operator-(const Mat<T> &A);
    Mat<T> operator*(const Mat<T> &A);
    Mat<T> operator/(const Mat<T> &A);



};


MATTEMPLATE
int Mat<T>::getCols() const{
    return this->cols;
}

MATTEMPLATE
int Mat<T>::getRows() const{
    return this->rows;
}
MATTEMPLATE
Mat<T>::Mat(){

}

MATTEMPLATE
//TODO: why private member can be read ?
Mat<T>::Mat(const Mat &A){
    this->cols=A.cols;
    this->rows=A.rows;
    this->data=A.data;
}

MATTEMPLATE
Mat<T>::Mat(int rows, int cols, INITTYPE type) {
    this->rows = rows;
    this->cols = cols;
    this->data= vector<vector<T>>(this->rows,vector<T>(this->cols));
    if(type==NONE){
        return;
    }
    if (type == ZEROS) {
        for (int i = 0; i < rows; i++) {
            this->data[i] = vector<T>(this->cols, 0);
        }
    } else if (type == ONES) {
        for (int i = 0; i < rows; i++) {
            this->data[i] = vector<T>(this->cols, 1);
        }
    } else if (type == RANDOM) {
        //TODO
    }
}
//TODO: to use iterator. typename
//MATTEMPLATE
//void Mat<T>::print() {
//    typename vector<vector<T>>::iterator iter1;
//    for (iter1 = (this->data).begin(); iter1 != (this->data).end(); iter1++) {
//        typename vector<T>::iterator iter2;
//        for (iter2 = (*iter1).begin(); iter2 != (*iter1).end(); iter2++) {
//            std::cout << *iter2 << " ";
//        }
//        std::cout << std::endl;
//    }
//}
MATTEMPLATE
void Mat<T>::print() const{
    for (int i = 0; i<this->rows; i++) {
        for (int j=0; j <this->cols; j++) {
            std::cout << this->data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

MATTEMPLATE
Mat<T>::~Mat() {

}

MATTEMPLATE
Mat<T> Mat<T>::matMul (const Mat<T> &A) const{
    Mat<T> B(this->rows,A.getCols(),ZEROS);
    for(int i=0;i<B.getRows();i++){
        for(int j=0;j<B.getCols();j++){
            for(int k=0;k<A.getRows();k++)
                B[i][j]+=(*this)[i][k]*A[k][j];
        }
    }
    return B;
}

MATTEMPLATE
vector<T>& Mat<T>::operator[](int i) {
    return this->data[i];
}

// const instance can only call const function member.
MATTEMPLATE
const vector<T>& Mat<T>::operator[](int i) const {
    return this->data[i];
}

MATTEMPLATE
Mat<T> Mat<T>::operator+(const Mat<T> &A) {
    Mat<T> B(this->rows,this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            B[i][j] = A[i][j] + (*this)[i][j];
        }
    }
    return B;
}

MATTEMPLATE
Mat<T> Mat<T>::operator-(const Mat<T> &A) {
    Mat<T> B(this->rows,this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            B[i][j] =  (*this)[i][j]-A[i][j];
        }
    }
    return B;
}
MATTEMPLATE
Mat<T> Mat<T>::operator*(const Mat<T> &A) {
    Mat<T> B(this->rows,this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            B[i][j] = A[i][j] * (*this)[i][j];
        }
    }
    return B;
}
MATTEMPLATE
Mat<T> Mat<T>::operator/(const Mat<T> &A) {
    Mat<T> B(this->rows,this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            B[i][j] = (*this)[i][j]/A[i][j];
        }
    }
    return B;
}
MATTEMPLATE
Mat<T> Mat<T>::subMat(span rows,span cols){
    int numRows=rows.b-rows.a;
    int numCols=cols.b-cols.a;
    Mat<T> A(numRows,numCols);
    for(int i=rows.a;i<rows.b;i++){
        for(int j=cols.a;j<cols.b;j++){
            T c=(*this)[i][j];
            A[i-rows.a][j-cols.b]=(*this)[i][j];
        }
    }
    return A;
}

#endif //MAT_MAT_H
