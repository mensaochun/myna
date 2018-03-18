//
// Created by yourenchun on 2018/3/15.
//

#ifndef FC_VEC_SOLVER_H
#define FC_VEC_SOLVER_H

#include "net.hpp"
class Net;
class Solver{
private:
    int maxIters;
    double learningRate;
    Net *net;
public:
    Solver(int iters,double learningRate,Net *net);
    void updateWeight();

    void run();

};

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
        std::cout<<"Iterarion:"<<i<<" ";
        this->net->step();
        this->updateWeight();
        std::cout<<"Loss:"<<this->net->calculateLoss()<<std::endl;
    }
    std::cout<<"Finish training..."<<std::endl;
}

#endif //FC_VEC_SOLVER_H
