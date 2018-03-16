//
// Created by yourenchun on 2018/3/15.
//
#include "solver.h"
Solver::Solver(int iters,double learningRate,Net *net) {
    this->learningRate=learningRate;
    this->maxIters=iters;
    this->net=net;
}
void Solver::updateWeight(){
    for(int i=1;i<net->numLayers;i++){
        net->layerList[i]->getWeight()=net->layerList[i]->getWeight()+learningRate*net->layerList[i]->getGradient();
    }
}
void Solver::run(){
    std::cout<<"Begin training..."<<std::endl;
    for(int i=0;i<maxIters;i++){
        std::cout<<"Iterarion:"<<i<<std::endl;
        this->net->step();
        this->updateWeight();
    }
    std::cout<<"Finish training..."<<std::endl;
}