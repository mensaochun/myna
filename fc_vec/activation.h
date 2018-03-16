//
// Created by yourenchun on 3/16/18.
//

#ifndef FC_VEC_ACTIVATION_H
#define FC_VEC_ACTIVATION_H

#include "mat.h"
#include "utils.h"
using namespace myna;

// class Activator---------------------

class Activator{
public:
    virtual Mat<double> forward(const Mat<double> &in,Mat<double> &out);
    virtual Mat<double> backward(const Mat<double> &in,Mat<double> &out);
};


// sigmoid
class SigmoidActivator:public Activator{
    virtual Mat<double> forward(const Mat<double> &in,Mat<double> &out);
    virtual Mat<double> backward(const Mat<double> &in,Mat<double> &out);
};

#endif //FC_VEC_ACTIVATION_H
