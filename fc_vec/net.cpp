//
// Created by yourenchun on 3/15/18.
//
#include "net.h"
Net::Net(Mat<double> &X,Mat<double> &Y) {
    this->numLayers = -1;
    this->X=X;
    this->Y=Y;
}

Net::~Net() {
    for(int i=0;i<layerList.size();i++){
        delete layerList[i];
    }
}

void Net::addInputLayer(const Mat<double> &X) {
    this->layerList.push_back(new InputLayer(X));
    this->numLayers++;
}

void Net::addFullyConnectedLayer(int numIn, int numOut) {
    FullyConnectedLayer *f = new FullyConnectedLayer(numIn, numOut, sigmoid);
    f->setInput(layerList[this->numLayers - 1]->getOutput());
    this->layerList.push_back(f);
    this->numLayers++;
}

void Net::addSigmoidLayer(int numIn, int numOut) {
    SigmoidLayer *s = new SigmoidLayer(numIn, numOut,this->Y);
    s->setInput(layerList[this->numLayers - 1]->getOutput());
    this->layerList.push_back(s);
    this->numLayers++;

}

void Net::step() {
    // forward
    for (int i = 1; i < this->numLayers; i++) {
        layerList[i]->forward();
    }

    // backword
    this->layerList[this->numLayers]->backword();
    for(int i=this->numLayers;i>=0;i--){
        layerList[i]->backword()
    }
}
