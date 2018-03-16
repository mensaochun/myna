//
// Created by yourenchun on 2/8/18.
//

#ifndef MAT_H
#define MAT_H

#define MATTEMPLATE template<typename T>

#include <iostream>
#include "assert.h"

namespace myna {
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

    struct SpanAll {};

    class Span {
    public:
        int a;
        int b;
        static const SpanAll all;

        Span(int in_a, int in_b);

        Span(int in_a);
    };

    MATTEMPLATE
    class Mat {
    private:
        int cols;
        int rows;
        T **data = nullptr;

    public:

        // only declare variables!
        Mat();

        // init variables, allocate memory, but not init
        Mat(int rows, int cols, Fill type = NONE);

        Mat(const Mat<T> &mat);

        ~Mat();

        void print() const;

        int getCols() const;

        int getRows() const;

        // can be read and written.Note:should not use A[i]!
        //TODO:need return T*&?
        T *operator[](int i);

        // can be only read.
        const T *operator[](int i) const;

        Mat<T> &operator=(const Mat<T> &M);

        Mat<T> operator+(const Mat<T> &A);

        Mat<T> operator-(const Mat<T> &A) const;

        Mat<T> operator*(const Mat<T> &A);

        /*
        friend Mat<T> operator*<T>(T scalar, const Mat<T> &A) {
            Mat<T> B(A.rows, A.cols);
            for (int i = 0; i < A.rows; i++) {
                for (int j = 0; j < A.cols; j++) {
                    B[i][j] = A[i][j] * scalar;
                }
            }
            return B;
        }
        /*
        friend Mat<T> operator*(const Mat<T> &A, T scalar) {
            Mat<T> B(A.rows, A.cols);
            for (int i = 0; i < A.rows; i++) {
                for (int j = 0; j < A.cols; j++) {
                    B[i][j] = A[i][j] * scalar;
                }
            }
            return B;
        }

        friend Mat<T> operator-(T scalar, const Mat<T> &A) {
            Mat<T> B(A.rows, A.cols);
            for (int i = 0; i < A.rows; i++) {
                for (int j = 0; j < A.cols; j++) {
                    B[i][j] = A[i][j] - scalar;
                }
            }
            return B;
        }

        friend Mat<T> operator-(const Mat<T> &A, T scalar) {
            Mat<T> B(A.rows, A.cols);
            for (int i = 0; i < A.rows; i++) {
                for (int j = 0; j < A.cols; j++) {
                    B[i][j] = scalar - A[i][j];
                }
            }
            return B;
        }
        */

        Mat<T> operator/(T scalar);

        Mat<T> operator/(const Mat<T> &in);

        Mat<T> operator()(Span rows, Span cols);

        Mat<T> operator()(SpanAll all, Span cols);

        Mat<T> operator()(Span rows, SpanAll cols);

        Mat<T> sum(Axis axis);

        Mat<T> mean(Axis axis);

        Mat<T> max(Axis axis);

        Mat<T> min(Axis axis);

        Mat<T> concatenate(const Mat<T> &in, Axis axis);

        Mat<T> transport();

        Mat<T> matMul(const Mat<T> &A) const;
    };
}

#endif //MAT_H
