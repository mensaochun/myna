//
// Created by yourenchun on 3/16/18.
//

#ifndef FC_VEC_ACTIVATION_H
#define FC_VEC_ACTIVATION_H

#include "../dataType/mat.hpp"
#include "utils.hpp"

using namespace myna;

// sigmoid
class Sigmoid {
public:
    static void forward(const Mat<double> &in, Mat<double> &out);

    static void backward(const Mat<double> &in, Mat<double> &out);
};

// relu
class Relu {
public:
    static void forward(const Mat<double> &in, Mat<double> &out);

    static void backward(const Mat<double> &in, Mat<double> &out);
};

// sigmoid
void Sigmoid::forward(const Mat<double> &in, Mat<double> &out) {
    sigmoid(in, out);
};

void Sigmoid::backward(const Mat<double> &in, Mat<double> &out) {
    Mat<double> a;
    sigmoid(in, a);
    out = a * (1.0 - a);//copy memory.
};

// relu
void Relu::forward(const Mat<double> &in, Mat<double> &out) {
    relu(in, out);
};

void Relu::backward(const Mat<double> &in, Mat<double> &out) {
    for (int i = 0; i < in.getRows(); i++) {
        for (int j = 0; j < in.getCols(); j++) {
            if (out[i][j] > 0) {
                out[i][j] = 1;
            } else {
                out[i][j] = 0;
            }
        }
    }
};

#endif //FC_VEC_ACTIVATION_H
