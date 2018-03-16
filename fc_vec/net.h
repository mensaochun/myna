//
// Created by yourenchun on 3/14/18.
//

#ifndef FC_VEC_NET_H
#define FC_VEC_NET_H

#include "utils.h"
#include "layer.h"
#include "solver.h"
#include <vector>

using namespace myna;
using std::vector;
class Solver;
class Net {
private:
    int numLayers;
    Mat<double> X;// n*m matrix, m is the number of the samples, and n is the number of the features.
    Mat<double> Y;// same as X.
    vector<BaseLayer *> layerList;
public:
    Net();

    Net(Mat<double> &X, Mat<double> &Y);

    void predict(const Mat<double> &input,Mat<double> &prediction);

    int getNumLayers();

    void addInputLayer(const Mat<double> &X);

    void addFullyConnectedLayer(int numIn, int numOut);

    void addSigmoidLayer(int numIn, int numOut, const Mat<double> &Y);

    void step();

    ~Net();

public:
    friend class Solver;
};


#endif //FC_VEC_NET_H
