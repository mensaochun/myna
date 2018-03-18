#include "solver.hpp"
#include <ctime>
using namespace myna;

int main(){

    // prepare data
    srand((unsigned)time(NULL));// set random seed.
    Mat<double> X(5,4,Fill::RANDOM);
    Mat<double> Y=X;
    Net net(X,Y);

    // construct layers
    net.addInputLayer(X);
    net.addFullyConnectedLayer(6,5);
    net.addFullyConnectedLayer(6,6);
    net.addFullyConnectedLayer(6,6);
    net.addSigmoidLayer(6,5,Y);

    // run solver for optimation
    Solver solver(10,0.1,&net);
    solver.run();

}