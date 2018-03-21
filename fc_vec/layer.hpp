//
// Created by yourenchun on 3/13/18.
//

#ifndef FC_VEC_LAYER_H
#define FC_VEC_LAYER_H

#include "mat/mat.hpp"
#include "utils.hpp"
#include "activation.hpp"

using namespace myna;
typedef void (*ptrActivation)(const Mat<double> &,Mat<double> &);//typedef activation function's pointer.

// ------------------BaseLayer-----------------
class BaseLayer {
protected:
    Mat<double> input;
    Mat<double> output;
    Mat<double> weight;
    Mat<double> delta;
    Mat<double> gradient;

public:
    virtual void setInput(const Mat<double> &in);
    virtual Mat<double> & getDelta();
    virtual Mat<double> & getOutput();
    virtual Mat<double> & getWeight();
    virtual Mat<double> & getGradient();
    virtual void forward();
    virtual void backward();
    virtual void backward(const Mat<double> &nextDelta);


};

// ---------------InputLayer-----------------
class InputLayer : public BaseLayer {

public:
    virtual Mat<double> & getOutput();
};


// ---------------FullyConnectedLayer-----------------
class FullyConnectedLayer : public BaseLayer {
private:
    Activator *activator;
public:
    //FullyConnectedLayer(int numIn, int numOut,ptrActivation pf);
    FullyConnectedLayer(int numIn, int numOut,Activator *activator);

    virtual void forward();

    virtual void backward(const Mat<double> &nextDelta);

};

class SigmoidLayer:public BaseLayer{
private:
    Mat<double> Y;
public:
    SigmoidLayer(int numIn,int numOut,const Mat<double> &Y);
    virtual void forward();
    virtual void backward();

};


// BaseLayer
void BaseLayer::setInput(const Mat<double> &input){
    Mat<double> oneMat(1,input.getCols(),Fill::ONES);
    this->input=input.concatenate(oneMat,Axis::ROW);
}
Mat<double> & BaseLayer::getOutput() {
    return this->output;
}
Mat<double>& BaseLayer::getDelta(){
    return this->delta;
}
Mat<double> & BaseLayer::getWeight(){
    return this->weight;
}
Mat<double> & BaseLayer::getGradient(){
    return this->gradient;
}

void BaseLayer::forward(){};
void BaseLayer::backward(){};
void BaseLayer::backward(const Mat<double> &nextDelta){};

// InputLayer
Mat<double>& InputLayer::getOutput() {
    return this->input;
}

// FullyConnetedLayer
//FullyConnectedLayer::FullyConnectedLayer(int numIn, int numOut,ptrActivation pf){
//    Mat<double> bias(numOut, 1, Fill::ZEROS);
//    Mat<double> weight_ = Mat<double>(numOut, numIn, Fill::RANDOM);
//    this->weight = weight_.concatenate(bias, Axis::COL);
//    this->activationFunction=pf;
//}

FullyConnectedLayer::FullyConnectedLayer(int numIn, int numOut,Activator *activator){
    Mat<double> bias(numOut, 1, Fill::ZEROS);
    Mat<double> weight_ = Mat<double>(numOut, numIn, Fill::RANDOM);
    this->weight = weight_.concatenate(bias, Axis::COL);
    this->activator=activator;
}

void FullyConnectedLayer::forward() {
    Mat<double> Z = weight.matMul(this->input);
    this->output=Mat<double>(Z.getRows(),Z.getCols());
    this->activator->forward(Z, this->output);
}

void FullyConnectedLayer::backward(const Mat<double> &nextDelta){
    Mat<double> weightTrans=this->weight.transport();
    Mat<double> derivative;
    this->activator->backward(this->output,derivative);
    this->delta=derivative*(weightTrans.matMul(nextDelta));
    this->gradient=this->delta.matMul(this->input.transport());
}


// SigmoidLayer
SigmoidLayer::SigmoidLayer(int numIn, int numOut,const Mat<double> &Y) {
    Mat<double> bias(numOut, 1, Fill::ZEROS);
    Mat<double> weight_ = Mat<double>(numOut, numIn, Fill::RANDOM);
    this->weight = weight_.concatenate(bias, Axis::COL);
    this->Y=Y;
}

void SigmoidLayer::forward() {
    sigmoid(this->input,this->output);
}

void SigmoidLayer::backward(){
    this->delta=output*(1.0-output)*(Y-output);
    this->gradient=delta.matMul(input.transport());
}


#endif //FC_VEC_LAYER_H
