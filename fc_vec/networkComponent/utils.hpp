//
// Created by yourenchun on 3/14/18.
//

#ifndef FC_VEC_UTILS_H
#define FC_VEC_UTILS_H

#include "../dataType/mat.hpp"
#include "math.h"

using namespace myna;

// sigmoid
double sigmoid(double x);
// element-wise sigmoid
void sigmoid(const Mat<double> &in, Mat<double> &out);
// relu
double relu(double x);
// element-wise relu
void relu(const Mat<double> &in, Mat<double> &out);


double sigmoid(double x) {
    double y = 1.0 / (1.0 + exp(-x));
    return y;
}

void sigmoid(const Mat<double> &in, Mat<double> &out) {
    int numRows = in.getRows();
    int numCols = in.getCols();
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            out[i][j] = sigmoid(in[i][j]);
        }
    }
}

// relu
double relu(double x) {
    if (x > 0) {
        return x;
    } else {
        return 0;
    }
}

void relu(const Mat<double> &in, Mat<double> &out) {
    int numRows = in.getRows();
    int numCols = in.getCols();
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            out[i][j] = relu(in[i][j]);
        }
    }
}

#endif //FC_VEC_UTILS_H
