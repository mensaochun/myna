//
// Created by yourenchun on 3/15/18.
//
#include "net.h"
Net::Net() {
}
Net::Net(Mat<double> &X,Mat<double> &Y) {
    this->numLayers = -1;
    this->X=X;
    this->Y=Y;
}

void Net::predict(const Mat<double> &input,Mat<double> &prediction){
    layerList[0]->setInput(input);
    for (int i = 1; i < this->numLayers; i++) {
        layerList[i]->forward();
    }
    prediction=layerList[this->numLayers]->getOutput();
}

int Net::getNumLayers(){
    return this->numLayers;
}
Net::~Net() {
    for(int i=0;i<layerList.size();i++){
        delete layerList[i];
    }
}

void Net::addInputLayer(const Mat<double> &X) {
    InputLayer *i=new InputLayer();
    i->setInput(X);
    this->layerList.push_back(i);
    this->numLayers++;
}

//void Net::addFullyConnectedLayer(int numIn, int numOut) {
//    FullyConnectedLayer *f = new FullyConnectedLayer(numIn, numOut, sigmoid);
//    //set input
//    f->setInput(layerList[this->numLayers - 1]->getOutput());
//    this->layerList.push_back(f);
//    this->numLayers++;
//}

void Net::addSigmoidLayer(int numIn, int numOut,const Mat<double> &Y) {
    SigmoidLayer *s = new SigmoidLayer(numIn, numOut,this->Y);
    s->setInput(layerList[this->numLayers - 1]->getOutput());
    this->layerList.push_back(s);
    this->numLayers++;

}

void Net::step() {
    // forward, begin from first layer.
    for (int i = 1; i < this->numLayers; i++) {
        layerList[i]->forward();
    }

    // backword, begin from last layer.
    for(int i=this->numLayers;i>=0;i--){
        if(i==this->numLayers){
            this->layerList[this->numLayers]->backward();
        }else{
            layerList[i]->backward(layerList[i+1]->getDelta());
        }
    }
}
