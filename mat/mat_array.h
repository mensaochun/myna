//
// Created by yourenchun on 2/8/18.
//

#ifndef MAT_H
#define MAT_H

#define MATTEMPLATE template<typename T>

#include <iostream>
#include "assert.h"

enum Fill {
    NONE,
    ZEROS,
    ONES,
    RANDOM
};

enum Axis {
    ROW,
    COL,
    BOTH
};

struct SpanAll {
};

class Span {
public:
    int a;
    int b;
    static const SpanAll all;

    Span(int in_a, int in_b) : a(in_a), b(in_b) {};

    Span(int in_a) : a(in_a), b(in_a) {};
};

const SpanAll Span::all = SpanAll();


MATTEMPLATE
class Mat {
private:
    int cols;
    int rows;
    T **data;

public:
    Mat() {};//std::cout<<"call constructor:Mat();"<<std::endl;};

    Mat(int rows, int cols, Fill type = NONE);

    Mat(const Mat<T> &mat);

    ~Mat();

    void print() const;

    int getCols() const;

    int getRows() const;

    // can be read and written.Note:should not use A[i]!
    //TODO:need return T*&?
    T *operator[](int i);

    //can be only read.
    const T *operator[](int i) const;

    Mat<T> &operator=(const Mat<T> &M);

    Mat<T> operator+(const Mat<T> &A);

    Mat<T> operator-(const Mat<T> &A);

    Mat<T> operator*(const Mat<T> &A);

    friend Mat<T> operator*(T scalar, const Mat<T> &A) {
        Mat<T> B(A.rows, A.cols);
        for (int i = 0; i < A.rows; i++) {
            for (int j = 0; j < A.cols; j++) {
                B[i][j] = A[i][j] * scalar;
            }
        }
        return B;
    }

    friend Mat<T> operator*(const Mat<T> &A, T scalar) {
        Mat<T> B(A.rows, A.cols);
        for (int i = 0; i < A.rows; i++) {
            for (int j = 0; j < A.cols; j++) {
                B[i][j] = A[i][j] * scalar;
            }
        }
        return B;
    }

    Mat<T> operator/(T scalar);

    Mat<T> operator/(const Mat<T> &in);

    Mat<T> operator()(Span rows, Span cols);

    Mat<T> operator()(SpanAll all, Span cols);

    Mat<T> operator()(Span rows, SpanAll cols);

    Mat<T> sum(Axis axis);

    Mat<T> mean(Axis axis);

    Mat<T> max(Axis axis);

    Mat<T> min(Axis axis);

    Mat<T> T();

    Mat<T> matMul(const Mat<T> &A) const;

    //TODO
    //friend Mat<T> sum(Mat<T> ...)

//    //load from txt.
//    void load();
//    //save to txt.
//    void save();
};

MATTEMPLATE
Mat<T> &Mat<T>::operator=(const Mat<T> &M) {
    //std::cout << "call operator=" << std::endl;
    if (this != &M) {
        this->rows = M.rows;
        this->cols = M.cols;
        //释放原来的内存
//        for (int i = 0; i < this->rows; i++) {
//            delete []this->data[i];
//        }
//        delete[]this->data;
        //分配新的内存
        this->data = new T *[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->data[i] = new T[this->cols];
        }
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                this->data[i][j] = M.data[i][j];
            }
        }

    }

    return *this;
}


MATTEMPLATE
Mat<T>::Mat(const Mat<T> &mat) {
    //std::cout << "call copy constructor!" << std::endl;
    this->rows = mat.rows;
    this->cols = mat.cols;
    //this->data= (T**)calloc(this->rows*this->cols, sizeof(T*));
    //memcpy(this->data, mat.data, (this->cols*this->rows) * sizeof(T));
    this->data = new T *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->data[i] = new T[this->cols];
    }
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            this->data[i][j] = mat.data[i][j];
        }
    }

}

MATTEMPLATE
Mat<T>::Mat(int rows, int cols, Fill type) {
    //std::cout<<"call constructor Mat(int rows, int cols, Fill type)."<<std::endl;
    this->rows = rows;
    this->cols = cols;
    // allocate memory
    this->data = new T *[this->rows];// create pointer array
    for (int i = 0; i < rows; i++) {
        this->data[i] = new T[this->cols];
    }

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (type == NONE) {
                return;
            } else if (type == ZEROS) {
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
Mat<T>::~Mat() {
    for (int i = 0; i < this->rows; i++) {
        delete[]data[i];
    }
    delete[]data;
}

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
int Mat<T>::getCols() const {
    return this->cols;
}

MATTEMPLATE
int Mat<T>::getRows() const {
    return this->rows;
}


MATTEMPLATE
T *Mat<T>::operator[](int i) {
    return this->data[i];

}

// const instance can only call const function member.
MATTEMPLATE
const T *Mat<T>::operator[](int i) const {
    return this->data[i];
}


MATTEMPLATE
Mat<T> Mat<T>::operator+(const Mat<T> &A) {
    //如果B是在栈上分配内存，由于B中的data是在堆中分配内存的，当B消亡之后，data对应的数据也析构了，因此无法return。
    //有两种办法解决：1.写一个拷贝构造函数（深拷贝）；2.B要在堆中进行创建。
    Mat<T> B(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            B[i][j] = A[i][j] + (*this)[i][j];
        }
    }
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
Mat<T> Mat<T>::operator/(T scalar) {
    Mat<T> B(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            B[i][j] = (*this)[i][j] / scalar;
        }
    }
    return B;
}

MATTEMPLATE
Mat<T> Mat<T>::operator/(const Mat<T> &in) {
    Mat<T> out(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            out[i][j] = (*this)[i][j] / in[i][j];
        }
    }
    return out;
}

MATTEMPLATE
Mat<T> Mat<T>::operator()(Span rows, Span cols) {
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
Mat<T> Mat<T>::operator()(SpanAll all, Span cols) {
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
Mat<T> Mat<T>::operator()(Span rows, SpanAll all) {
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
Mat<T> Mat<T>::sum(Axis axis) {
    Mat mat;
    if (axis == Axis::ROW) {
        mat = Mat(1, this->cols, ZEROS);
        for (int j = 0; j < this->cols; j++) {
            for (int i = 0; i < this->rows; i++) {
                mat[0][j] += this->data[i][j];
            }
        }
    } else if (axis == Axis::COL) {
        mat = Mat(this->rows, 1, ZEROS);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                mat[i][0] += this->data[i][j];
            }
        }
    } else if (axis == Axis::BOTH) {
        mat = Mat(1, 1,ZEROS);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                mat[0][0] += this->data[i][j];
            }
        }
    }
    return mat;
}

MATTEMPLATE
Mat<T> Mat<T>::mean(Axis axis) {
    Mat mat;
    if (axis == Axis::ROW) {
        mat = this->sum(Axis::ROW);
        mat = mat / this->rows;
    } else if (axis == Axis::COL) {
        mat = this->sum(Axis::COL);
        mat = mat / this->cols;
    } else if (axis == Axis::BOTH) {
        mat = this->sum(Axis::BOTH);
        mat = mat / (this->rows * this->cols);
    }
    return mat;
}

MATTEMPLATE
Mat<T> Mat<T>::matMul(const Mat<T> &in) const {
    Mat<T> out(this->rows, in.getCols());
    for (int i = 0; i < out.getRows(); i++) {
        for (int j = 0; j < out.getCols(); j++) {
            for (int k = 0; k < in.getRows(); k++)
                out[i][j] += this->data[i][k] * in[k][j];
        }
    }
    return out;
}

MATTEMPLATE
Mat<T> Mat<T>::max(Axis axis) {
    // call constructor.
    Mat<T> M;
    if (axis == ROW) {
        //why not call copy constructor? Because it is assignment and it will call operator=.
        M = Mat<T>(1, this->cols, Fill::ZEROS);
        for (int j = 0; j < this->cols; j++) {
            M[0][j] = this->data[0][j];
            for (int i = 0; i < this->rows - 1; i++) {
                if (M[0][j] < this->data[i + 1][j]) {
                    M[0][j] = this->data[i + 1][j];
                }
            }
        }
    } else if (axis == COL) {
        M = Mat<T>(this->rows, 1, Fill::ZEROS);
        for (int i = 0; i < this->rows; i++) {
            M[i][0] = this->data[i][0];
            for (int j = 0; j < this->cols - 1; j++) {
                if (M[i][0] < this->data[i][j + 1]) {
                    M[i][0] = this->data[i][j + 1];
                }
            }
        }
    } else if (axis == BOTH) {
        M = Mat<T>(1, 1, Fill::ZEROS);
        T max = this->data[0][0];
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                if (max < this->data[i][j]) {
                    max = this->data[i][j];
                }
            }
        }
        M[0][0] = max;
    }
    /*
     * return M will call copy constructor, but it may be not actually called!
     * more details,see:http://c.biancheng.net/cpp/biancheng/view/3286.html
     * 在较老的编译器上，你或许真的能够看到调用两次拷贝构造函数，例如 iPhone 上的 C/C++ 编译器。
     * 但是在现代编译器上，只会调用一次拷贝构造函数，或者一次也不调用，例如在 VS2010 下会调用一次
     * 拷贝构造函数，在 GCC、Xcode 下一次也不会调用。这是因为，现代编译器都支持返回值优化技术，会
     * 尽量避免拷贝对象，以提高程序运行效率。关于编译器如何实现返回值优化的我们不再展开讨论。
     */
    return M;
}

MATTEMPLATE
Mat<T> Mat<T>::min(Axis axis) {
    // call constructor.
    Mat<T> M;
    if (axis == ROW) {
        //why not call copy constructor? Because it is assignment and it will call operator=.
        M = Mat<T>(1, this->cols, Fill::ZEROS);
        for (int j = 0; j < this->cols; j++) {
            M[0][j] = this->data[0][j];
            for (int i = 0; i < this->rows - 1; i++) {
                if (M[0][j] > this->data[i + 1][j]) {
                    M[0][j] = this->data[i + 1][j];
                }
            }
        }
    } else if (axis == COL) {
        M = Mat<T>(this->rows, 1, Fill::ZEROS);
        for (int i = 0; i < this->rows; i++) {
            M[i][0] = this->data[i][0];
            for (int j = 0; j < this->cols - 1; j++) {
                if (M[i][0] > this->data[i][j + 1]) {
                    M[i][0] = this->data[i][j + 1];
                }
            }
        }
    } else if (axis == BOTH) {
        M = Mat<T>(1, 1, Fill::ZEROS);
        T max = this->data[0][0];
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                if (max > this->data[i][j]) {
                    max = this->data[i][j];
                }
            }
        }
        M[0][0] = max;
    }
    return M;
}

MATTEMPLATE
Mat<T> Mat<T>::T(){
    Mat<T> M(this->cols,this->rows);
    
}

//---------------------------test----------------

void test_operator_mul_1() {
    Mat<int> A(3, 3, ONES);
    Mat<int> B = A * 3;
    B.print();
}


void test_operator_brackets() {
    Mat<int> A(4, 4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            A[i][j] = i + j;
        }
    }
    A.print();
    std::cout<<std::endl;
    Mat<int> B = A(Span(0, 2), Span(1, 2));
    B.print();
    std::cout<<std::endl;
    Mat<int> C = A(Span::all, Span(1, 4));
    C.print();
    std::cout<<std::endl;
    Mat<int> D = A(Span(0, 2), Span::all);
    D.print();
}

void test_operator_add() {
    Mat<int> A(2, 3, ZEROS);
    Mat<int> B(2, 3, ONES);
    Mat<int> C = A + B;
    C.print();
}

void test_operator_bracket_help_func(const Mat<int> A) {
    std::cout << A[0][0] << std::endl;
}

void test_operator_square_brackets() {
    Mat<int> A(2, 2, ONES);
    test_operator_bracket_help_func(A);
    A[0][0] = 3;
    std::cout << A[0][0];
}

void test_sum() {
    Mat<int> A(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = i + j;
        }
    }
    Mat<int> B = A.sum(Axis::ROW);
    Mat<int> C = A.sum(Axis::COL);
    Mat<int> D = A.sum(Axis::BOTH);
    A.print();
    std::cout<<std::endl;
    B.print();
    std::cout<<std::endl;
    C.print();
    std::cout<<std::endl;
    D.print();

}

void test_matMul() {
    Mat<int> A(2, 3, ONES);
    Mat<int> B(3, 4, ONES);
    Mat<int> C = A.matMul(B);

    A.print();
    std::cout << std::endl;
    B.print();
    std::cout << std::endl;
    C.print();
}

void test_mean() {
    Mat<int> A(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = i + j;
        }
    }
    Mat<int> B = A.mean(Axis::ROW);
    Mat<int> C = A.mean(Axis::COL);
    Mat<int> D = A.mean(Axis::BOTH);
    A.print();
    std::cout<<std::endl;
    B.print();
    std::cout<<std::endl;
    C.print();
    std::cout<<std::endl;
    D.print();
}

void test_max() {
    Mat<int> A(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = i + j;
        }
    }
    A.print();
    std::cout << std::endl;
    Mat<int> B = A.max(Axis::ROW);
    B.print();

    std::cout << std::endl;
    Mat<int> C = A.max(Axis::COL);
    C.print();

    std::cout << std::endl;
    Mat<int> D = A.max(Axis::BOTH);
    D.print();

}

void test_min() {
    Mat<int> A(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = i + j;
        }
    }
    A.print();
    std::cout << std::endl;
    Mat<int> B = A.min(Axis::ROW);
    B.print();

    std::cout << std::endl;
    Mat<int> C = A.min(Axis::COL);
    C.print();

    std::cout << std::endl;
    Mat<int> D = A.min(Axis::BOTH);
    D.print();

}



#endif //MAT_H
