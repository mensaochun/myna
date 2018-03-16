//
// Created by yourenchun on 3/16/18.
//

#include "activation.h"
// Activator-----------------------
Mat<double> Activator::forward(const Mat<double> &in,Mat<double> &out){};
Mat<double> Activator::backward(const Mat<double> &in,Mat<double> &out){};

// SigmoidActivator----------------
Mat<double> SigmoidActivator::forward(const Mat<double> &in,Mat<double> &out){
    sigmoid(in,out);
};
Mat<double> SigmoidActivator::backward(const Mat<double> &in,Mat<double> &out){
    Mat<double> s;
    sigmoid(in,s);
    out=s*(1.0-s);//copy memory.
};

// ReluActivator----------------