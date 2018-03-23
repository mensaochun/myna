//
// Created by yourenchun on 3/16/18.
//

#ifndef FC_VEC_ACTIVATION_H
#define FC_VEC_ACTIVATION_H

#include "../dataType/mat.hpp"
#include "utils.hpp"

using namespace myna;

// class Activator---------------------

class Activator {
public:
    virtual Mat<double> forward(const Mat<double> &in, Mat<double> &out);

    virtual Mat<double> backward(const Mat<double> &in, Mat<double> &out);
};


// sigmoid
class SigmoidActivator : public Activator {
    virtual Mat<double> forward(const Mat<double> &in, Mat<double> &out);

    virtual Mat<double> backward(const Mat<double> &in, Mat<double> &out);
};


// Activator-----------------------
Mat<double> Activator::forward(const Mat<double> &in, Mat<double> &out) {};

Mat<double> Activator::backward(const Mat<double> &in, Mat<double> &out) {};

// SigmoidActivator----------------
Mat<double> SigmoidActivator::forward(const Mat<double> &in, Mat<double> &out) {
    sigmoid(in, out);
};

Mat<double> SigmoidActivator::backward(const Mat<double> &in, Mat<double> &out) {
    Mat<double> s;
    sigmoid(in, s);
    out = s * (1.0 - s);//copy memory.
};


#endif //FC_VEC_ACTIVATION_H
