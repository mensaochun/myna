//
// Created by yourenchun on 3/13/18.
//

#ifndef FC_VEC_LAYER_H
#define FC_VEC_LAYER_H

#include "../dataType/mat.hpp"
#include "utils.hpp"
#include "activation.hpp"
#include <vector>
using std::vector;
using namespace myna;

// ------------------BaseLayer-----------------
class BaseLayer {
protected:
    Mat<double> *input;//share memory with previous layer. So it is a pointer.
    Mat<double> output;
    std::vector<Mat<double>> weights;// contain weight and bias.
    std::vector<Mat<double>> gradients;// contain gradient of weight and bias.
    Mat<double> delta;

public:
    virtual void setInput(Mat<double> *in);

    virtual Mat<double> &getDelta();

    virtual Mat<double> &getOutput();

//    virtual vector<Mat<double>> &getWeight();

//    virtual Mat<double> &getGradient();

    virtual void forward();

    virtual void backward();

    virtual void backward(const Mat<double> &nextDelta);


};

// ---------------InputLayer-----------------
class InputLayer : public BaseLayer {
private:
    Mat<double> input;

public:
    virtual void setInput(const Mat<double> &X);
    virtual Mat<double> &getOutput(); // to return input due to input=output
};


// ---------------FullyConnectedLayer-----------------
template<typename Activator>
class FullyConnectedLayer : public BaseLayer {
public:

    FullyConnectedLayer(int numIn, int numOut);

    virtual void forward();

    virtual void backward(const Mat<double> &nextDelta);

};

class SigmoidLayer : public BaseLayer {
private:
    Mat<double> Y;
public:
    SigmoidLayer(int numIn, int numOut, const Mat<double> &Y);

    virtual void forward();

    virtual void backward();

};


// BaseLayer
void BaseLayer::setInput(Mat<double> *in) {
    this->input = in;
}

Mat<double> &BaseLayer::getOutput() {
    return output;
}

Mat<double> &BaseLayer::getDelta() {
    return delta;
}

//vector<Mat<double>> &BaseLayer::getWeight() {
//    return weights;
//}
//
//Mat<double> &BaseLayer::getGradient() {
//    return gradient;
//}

void BaseLayer::forward() {};

void BaseLayer::backward() {};

void BaseLayer::backward(const Mat<double> &nextDelta) {};

// InputLayer

void InputLayer::setInput(const Mat<double> &X){
    input=X;
}

Mat<double> &InputLayer::getOutput() {
    return input;
}

// FullyConnetedLayer
//FullyConnectedLayer::FullyConnectedLayer(int numIn, int numOut,ptrActivation pf){
//    Mat<double> bias(numOut, 1, Fill::ZEROS);
//    Mat<double> weight_ = Mat<double>(numOut, numIn, Fill::RANDOM);
//    this->weight = weight_.concatenate(bias, Axis::COL);
//    this->activationFunction=pf;
//}

FullyConnectedLayer::FullyConnectedLayer(int numIn, int numOut) {
    bias = Mat<double>(numOut, 1, Fill::ZEROS);
    weight = Mat<double>(numOut, numIn, Fill::RANDOM);
}

void FullyConnectedLayer::forward() {
    Mat<double> Z = weight.matMul(input).matAddVec(bias);
    output = Mat<double>(Z.getRows(), Z.getCols());
    activator->forward(Z, output);
}

void FullyConnectedLayer::backward(const Mat<double> &nextDelta) {
    Mat<double> weightTrans = weight.transport();
    Mat<double> derivative;
    activator->backward(output, derivative);
    delta = derivative * (weightTrans.matMul(nextDelta));
    gradient = delta.matMul(input.transport());
}


// SigmoidLayer
SigmoidLayer::SigmoidLayer(int numIn, int numOut, const Mat<double> &Y) {
    bias = Mat<double>(numOut, 1, Fill::ZEROS);
    weight = Mat<double>(numOut, numIn, Fill::RANDOM);
    this->Y = Y;
}

void SigmoidLayer::forward() {
    sigmoid(input, output);
}

void SigmoidLayer::backward() {
    delta = output * (1.0 - output) * (Y - output);
    gradient = delta.matMul(input.transport());
}


#endif //FC_VEC_LAYER_H
