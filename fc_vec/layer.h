//
// Created by yourenchun on 3/13/18.
//

#ifndef FC_VEC_LAYER_H
#define FC_VEC_LAYER_H

#include "mat.h"
#include "utils.h"

using namespace myna;
typedef void (*ptrActivation)(const Mat<double> &,Mat<double> &);//typedef activation function's pointer.

// ------------------BaseLayer-----------------
class BaseLayer {
protected:
    Mat<double> input;
    Mat<double> output;

public:
    virtual void setInput(const Mat<double> &in);
    virtual Mat<double> & getOutput();
    virtual void forward();
    virtual void backword(const Mat<double> &nextDelta);
    virtual void backword(const Mat<double> &nextDelta,const Mat<double> &target);
};

// ---------------InputLayer-----------------
class InputLayer : public BaseLayer {

public:
    InputLayer(const Mat<double> &in);
    virtual Mat<double> & getOutput();
};


// ---------------FullyConnectedLayer-----------------
class FullyConnectedLayer : public BaseLayer {
private:
    Mat<double> delta;
    Mat<double> gradient;
    Mat<double> weight;
    ptrActivation activationFunction;
public:
    FullyConnectedLayer(int numIn, int numOut,ptrActivation pf);

    virtual void forward();

    virtual void backward(const Mat<double> &nextDelta);

};

class SigmoidLayer:public BaseLayer{
private:
    Mat<double> delta;
    Mat<double> gradient;
    Mat<double> weight;
    Mat<double> Y;
public:
    SigmoidLayer(int numIn,int numOut,const Mat<double> &Y);
    const Mat<double> & setTarget(const Mat<double> &Y);
    virtual void forward();
    virtual void backward(const Mat<double> &nextDelta,const Mat<double> &target);

};

#endif //FC_VEC_LAYER_H
