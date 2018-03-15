//
// Created by yourenchun on 3/15/18.
//

#include "layer.h"

// BaseLayer
void BaseLayer::forward() {}
void BaseLayer::backword(const Mat<double> &nextDelta){};
void BaseLayer::backword(const Mat<double> &nextDelta,const Mat<double> &target){};
void BaseLayer::setInput(const Mat<double> &input){
    this->input=input;
}

Mat<double> & BaseLayer::getOutput() {
    return this->output;
}

// InputLayer
InputLayer::InputLayer(const Mat<double> &in) :{
    this->setInput(in);//TODO, virtual function can be directly called by Son class?
}
Mat<double>& InputLayer::getOutput() {
    return this->input;
}

// FullyConnetedLayer
FullyConnectedLayer::FullyConnectedLayer(int numIn, int numOut,ptrActivation pf){
    Mat<double> bias(numOut, 1, Fill::ZEROS);
    Mat<double> weight_ = Mat<double>(numOut, numIn, Fill::RANDOM);
    this->weight = weight_.concatenate(bias, Axis::COL);
    this->activationFunction=pf;
}

void FullyConnectedLayer::forward() {
    Mat<double> Z = weight.matMul(this->input);
    this->activationFunction(Z, this->output);
}
void FullyConnectedLayer::backward(const Mat<double> &nextDelta){
    Mat<double> weightTrans=this->weight.transport();
    this->delta=(this->output)*(1.0-this->output)*(weightTrans.matMul(nextDelta));
    this->gradient=this->delta.matMul(this->input.transport());
}


// SigmoidLayer
SigmoidLayer::SigmoidLayer(int numIn, int numOut,const Mat<double> &Y) {
    Mat<double> bias(numOut, 1, Fill::ZEROS);
    Mat<double> weight_ = Mat<double>(numOut, numIn, Fill::RANDOM);
    this->weight = weight_.concatenate(bias, Axis::COL);
    this->Y=this->setTarget(Y);
}

const Mat<double> & SigmoidLayer::setTarget(const Mat<double> &Y){
    return Y;
}
void SigmoidLayer::forward() {
    sigmoid(this->input,this->output);
}

void SigmoidLayer::backward(const Mat<double> &nextDelta,const Mat<double> &target){
    this->delta=this->output*(1.0-this->output)*(target-this->output);
    this->gradient=this->delta.matMul(this->input.transport());
}
