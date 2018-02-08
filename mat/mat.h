//
// Created by yourenchun on 2/8/18.
//

#ifndef MAT_MAT_H
#define MAT_MAT_H

#define MATTEMPLATE template<typename T>

#include <iostream>


MATTEMPLATE
enum INITTYPE{
    std ZEROS;
    ONES;
    RANDOMS;
};

class Mat {
private:
    int cols;
    int rows;
    T **data;

public:
    Mat(int rows,int cols) {
        this->rows=rows;
        this->cols=cols;
        // allocate memory
        this->data=new T*[this->rows];// create pointer array
        for(int i=0;i<rows;i++){
            this->data[i]=new T[this->cols];
        }
        // init with zeros
        for(int i=0;i<this->cols;i++){
            for(int j=0;j<this->rows;j++){
                this->data[i][j]=0;
            }
        }
    }

    Mat(int rows,int cols) {
        this->rows=rows;
        this->cols=cols;
        // allocate memory
        this->data=new T*[this->rows];// create pointer array
        for(int i=0;i<rows;i++){
            this->data[i]=new T[this->cols];
        }
        // init with zeros
        for(int i=0;i<this->cols;i++){
            for(int j=0;j<this->rows;j++){
                this->data[i][j]=0;
            }
        }
    }

    Mat<T> operator+(const Mat<T> &A){
        Mat<T> B(this->rows,this->cols);
    }
};


#endif //MAT_MAT_H
