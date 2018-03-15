//
// Created by yourenchun on 3/15/18.
//

#include "layer.h"

// BaseLayer
void BaseLayer::setInput(const Mat<double> &input){
    this->input=input;
}
Mat<double> & BaseLayer::getOutput() {
    return this->output;
}
Mat<double>& BaseLayer::getDelta(){
    return this->delta;
}
void BaseLayer::forward(){};
void BaseLayer::backward(){};
void BaseLayer::backward(const Mat<double> &nextDelta){};
void BaseLayer::updateWeight(const Mat<double> &gradient,double learningRate){
    this->weight=this->weight+learningRate*gradient;
}
// InputLayer
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
    this->Y=Y;
}

void SigmoidLayer::forward() {
    sigmoid(this->input,this->output);
}

void SigmoidLayer::backward(){
    this->delta=this->output*(1.0-this->output)*(this->Y-this->output);
    this->gradient=this->delta.matMul(this->input.transport());
}
