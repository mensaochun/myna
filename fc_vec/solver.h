//
// Created by yourenchun on 2018/3/15.
//

#ifndef FC_VEC_SOLVER_H
#define FC_VEC_SOLVER_H

#include "net.h"
class Solver{
private:
private:
    int maxIters;
    double learningRate;
    Net net;
public:
    Solver(int iters,double learningRate,const Net &net);
    void run();
};


#endif //FC_VEC_SOLVER_H
