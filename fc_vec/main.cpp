#include "solver.hpp"
#include <ctime>
using namespace myna;
// help function:print()

void printMat(Mat<double> X){
    for(int i=0;i<X.getRows();i++){
        for(int j=0;j<X.getCols();j++){
            std::cout<<X[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
int main(){

    // prepare data
    srand((unsigned)time(NULL));// set random seed.
    Mat<double> X(5,4,Fill::RANDOM);
    Mat<double> Y=X;
    Net net(X,Y);

    // construct layers
    net.addInputLayer(X);
    net.addFullyConnectedLayer(5,6,new SigmoidActivator);
    net.addFullyConnectedLayer(6,6,new SigmoidActivator);
    net.addFullyConnectedLayer(6,6,new SigmoidActivator);
    net.addSigmoidLayer(6,5,Y);

    // run solver for optimation
    Solver solver(10,0.1,&net);
    solver.run();

}