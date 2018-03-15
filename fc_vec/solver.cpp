//
// Created by yourenchun on 2018/3/15.
//
#include "solver.h"
Solver::Solver(int iters,double learningRate,const Net &net) {
    this->learningRate=learningRate;
    this->maxIters=iters;
    this->net=net;
}

void Solver::run() {

}