//
// Created by yourenchun on 3/14/18.
//

#ifndef FC_VEC_ACTIVATION_H
#define FC_VEC_ACTIVATION_H

#include "mat.h"
#include <math.h>
using namespace myna;
double sigmoid(double x){
    int y=1.0/(1.0+exp(-x));
    return y;
}
void sigmoid(const Mat<double> &in,Mat<double> &out){
    int numRows=in.getRows();
    int numCols=in.getCols();
    for(int i=0;i<numRows;i++){
        for(int j=0;j<numCols;j++){
           out[i][j]=sigmoid(in[i][j]);
        }
    }
}

#endif //FC_VEC_ACTIVATION_H
