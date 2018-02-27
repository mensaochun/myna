/*
 Created by yourenchun on 2/8/18.
 matrix operator library.
*/

#ifndef MAT_MAT_H
#define MAT_MAT_H

#define MATTEMPLATE template<typename T>

#include <iostream>
#include <vector>
#include"assert.h"

using std::vector;
enum INITTYPE {
    NONE,
    ZEROS,
    ONES,
    RANDOM
};

enum DIRECTION {
    row,
    col,
    both
};

class span {

public:
    static const int all = 0;
    // a,b are zero-based index and not include b.
    int a;
    int b;

    span(int a, int b) {
        this->a = a;
        this->b = b;
    }
};


void test();

MATTEMPLATE
class Mat {
private:
    int cols;
    int rows;
    vector<vector<T>> data;

public:
    Mat();

    Mat(const Mat &A);//default constructor
    Mat(int rows, int cols, INITTYPE type = ZEROS);//default: None

    ~Mat();

    int getCols() const;

    int getRows() const;

    void print() const;

    Mat<T> matMul(const Mat<T> &A) const;

    Mat<T> subMat(span rows, span cols);

    Mat<T> subMat(const int all, span cols);

    Mat<T> subMat(span rows, const int all);

    const vector<T> &operator[](int i) const;

    vector<T> &operator[](int i);

    // element-wise + - *
    Mat<T> operator+(const Mat<T> &A);

    Mat<T> operator-(const Mat<T> &A);

    Mat<T> operator*(const Mat<T> &A);

    // all elements divided by num val.
    Mat<T> operator/(const T val);

    // math operator
    Mat<T> sum(DIRECTION direction);

    Mat<T> mean(DIRECTION direciton);

};


MATTEMPLATE
int Mat<T>::getCols() const {
    return this->cols;
}

MATTEMPLATE
int Mat<T>::getRows() const {
    return this->rows;
}

MATTEMPLATE
Mat<T>::Mat() {

}

MATTEMPLATE
//TODO: why private member can be read ?
Mat<T>::Mat(const Mat &A) {
    //std::cout<<"Call copy constructor"<<std::endl;
    this->cols = A.cols;
    this->rows = A.rows;
    this->data = A.data;
}

MATTEMPLATE
Mat<T>::Mat(int rows, int cols, INITTYPE type) {
    this->rows = rows;
    this->cols = cols;
    // only determine the number of rows and columns.
    this->data = vector<vector<T>>(this->rows, vector<T>(this->cols));
    if (type == ZEROS) {
        // not init data
        return;
    } else if (type == ONES) {
        for (int i = 0; i < this->rows; i++) {
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
void Mat<T>::print() const {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            std::cout << this->data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

MATTEMPLATE
Mat<T>::~Mat() {

}

MATTEMPLATE
Mat<T> Mat<T>::matMul(const Mat<T> &A) const {
    Mat<T> B(this->rows, A.getCols(), ZEROS);
    for (int i = 0; i < B.getRows(); i++) {
        for (int j = 0; j < B.getCols(); j++) {
            for (int k = 0; k < A.getRows(); k++)
                B[i][j] += (*this)[i][k] * A[k][j];
        }
    }
    return B;
}

MATTEMPLATE
vector<T> &Mat<T>::operator[](int i) {
    // Note: must return reference.
    return this->data[i];
}

// const instance can only call const function member. So must reload the operator [] with const constrain.
MATTEMPLATE
const vector<T> &Mat<T>::operator[](int i) const {
    return this->data[i];
}

MATTEMPLATE
Mat<T> Mat<T>::operator+(const Mat<T> &A) {
    Mat<T> B(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            B[i][j] = A[i][j] + (*this)[i][j];
        }
    }
    // copy B.
    return B;
}

MATTEMPLATE
Mat<T> Mat<T>::operator-(const Mat<T> &A) {
    Mat<T> B(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            B[i][j] = (*this)[i][j] - A[i][j];
        }
    }
    return B;
}

MATTEMPLATE
Mat<T> Mat<T>::operator*(const Mat<T> &A) {
    Mat<T> B(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            B[i][j] = A[i][j] * (*this)[i][j];
        }
    }
    return B;
}

MATTEMPLATE
Mat<T> Mat<T>::operator/(const T val) {
    Mat<T> B(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            B[i][j] = (*this)[i][j] / val;
        }
    }
    return B;
}

MATTEMPLATE
Mat<T> Mat<T>::subMat(span rows, span cols) {
    assert(rows.a >= 0 && rows.b > rows.a && rows.b <= this->rows);
    assert(cols.a >= 0 && cols.b > cols.a && cols.b <= this->cols);
    int numRows = rows.b - rows.a;
    int numCols = cols.b - cols.a;
    Mat<T> A(numRows, numCols);
    for (int i = rows.a; i < rows.b; i++) {
        for (int j = cols.a; j < cols.b; j++) {
            A[i - rows.a][j - cols.a] = (*this)[i][j];
        }
    }
    return A;
}

MATTEMPLATE
Mat<T> Mat<T>::subMat(const int all, span cols) {
    assert(cols.a >= 0 && cols.b > cols.a && cols.b <= this->cols);
    int numRows = this->rows;
    int numCols = cols.b - cols.a;
    Mat<T> A(numRows, numCols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = cols.a; j < cols.b; j++) {
            A[i][j - cols.a] = (*this)[i][j];
        }
    }
    return A;
}

MATTEMPLATE
Mat<T> Mat<T>::subMat(span rows, const int all) {
    assert(rows.a >= 0 && rows.b > rows.a && rows.b <= this->rows);
    int numRows = rows.b - rows.a;
    int numCols = this->cols;
    Mat<T> A(numRows, numCols);
    for (int i = rows.a; i < rows.b; i++) {
        for (int j = 0; j < this->cols; j++) {
            A[i - rows.a][j] = (*this)[i][j];
        }
    }
    return A;
}

MATTEMPLATE
Mat<T> Mat<T>::sum(DIRECTION direction) {
    Mat mat;
    if (direction == DIRECTION::row) {
        mat = Mat(1, this->cols);
        for (int j = 0; j < this->cols; j++) {
            for (int i = 0; i < this->rows; i++) {
                mat[0][j] += (*this)[i][j];
            }
        }
    } else if (direction == DIRECTION::col) {
        mat = Mat(this->rows, 1);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                mat[i][0] += (*this)[i][j];
            }
        }
    } else if (direction == DIRECTION::both) {
        mat = Mat(1, 1);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                mat[0][0] += (*this)[i][j];
            }
        }
    }
    return mat;
}

MATTEMPLATE
Mat<T> Mat<T>::mean(DIRECTION direction) {
    Mat mat;
    if (direction == DIRECTION::row) {
        mat = this->sum(DIRECTION::row);
        mat = mat / this->rows;
    } else if (direction == DIRECTION::col) {
        mat = this->sum(DIRECTION::col);
        mat = mat / this->cols;
    } else if (direction == DIRECTION::both) {
        mat = this->sum(DIRECTION::both);
        mat = mat / (this->rows * this->cols);
    }
    return mat;
}

void test() {
    //test Mat() and print()
    Mat<int> mat_1;
    std::cout << "mat_1:" << std::endl;
    //Note: can call print()!
    //mat_1.print();

    //test Mat(int rows, int cols, INITTYPE type)
    Mat<int> mat_2(3, 4, INITTYPE::ZEROS);
    std::cout << "mat_2:" << std::endl;
    mat_2.print();
    Mat<int> mat_3(3, 4, INITTYPE::ONES);
    std::cout << "mat_3:" << std::endl;
    mat_3.print();

    //test Mat(const Mat &A)
    Mat<int> mat_4 = mat_3;
    mat_4.print();

    //test getCols() and getRows()
    std::cout << "mat_4 cols:" << mat_4.getCols() << std::endl;
    std::cout << "mat_4 rows:" << mat_4.getRows() << std::endl;

    //test matMul(const Mat<T> &A)
    Mat<int> mat_5 = Mat<int>(2, 3, ONES);
    Mat<int> mat_6 = Mat<int>(3, 4, ONES);
    Mat<int> mat_7 = mat_5.matMul(mat_6);
    std::cout << "mat_7:" << std::endl;
    /* Bug:var-create unable to create variable object
     * Please refer to https://stackoverflow.com/questions/41854840/var-create-unable-to-create-variable-object
     * */
    mat_7.print();

    //test subMat(span rows,span cols)
    Mat<int> mat_8 = Mat<int>(5, 4, ONES);
    std::cout << "mat_8:" << std::endl;
    mat_8.print();
    Mat<int> mat_9 = mat_8.subMat(span(2, 4), span(0, 4));
    std::cout << "mat_9:" << std::endl;
    mat_9.print();

    //test subMat(std::string is_all,span cols);
    Mat<int> mat_10 = mat_8.subMat(span::all, span(0, 3));
    std::cout << "mat_10:" << std::endl;
    mat_10.print();

    //test subMat(span rows,std::string is_all);
    Mat<int> mat_11 = mat_8.subMat(span(1, 4), span::all);
    std::cout << "mat_11:" << std::endl;
    mat_11.print();

    //test operator+(const Mat<T> &A);
    Mat<int> A(3, 4, ONES);
    Mat<int> B(3, 4, ONES);
    Mat<int> C = A + B;
    std::cout << "mat_C:" << std::endl;
    C.print();
    //test operator-(const Mat<T> &A);
    Mat<int> D = A - B;
    std::cout << "mat_D:" << std::endl;
    D.print();
    //test operator*(const Mat<T> &A);
    Mat<int> E = A * B;
    std::cout << "mat_E:" << std::endl;
    E.print();
    //test operator/(const Mat<T> &A);

    //test sum()
    Mat<int> a(10, 10, ONES);
    Mat<int> b = a.sum(DIRECTION::row);
    std::cout << "b:" << std::endl;
    b.print();
    Mat<int> c = a.sum(DIRECTION::col);
    std::cout << "c:" << std::endl;
    c.print();
    Mat<int> d = a.sum(DIRECTION::both);
    std::cout << "d:" << std::endl;
    d.print();

    //test mean()
    Mat<int> e = a.mean(DIRECTION::row);
    std::cout << "e:" << std::endl;
    e.print();
    Mat<int> f = a.mean(DIRECTION::col);
    std::cout << "f:" << std::endl;
    f.print();
    Mat<int> g = a.mean(DIRECTION::both);
    std::cout << "g:" << std::endl;
    g.print();

}

#endif //MAT_MAT_H



