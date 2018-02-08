//
// Created by pi on 2/8/18.
//

#include "include/kmeans.h"

int main(){
    // test mnist
//    string X_file="./data/mnist/images.txt";
//    string y_file="./data/mnist/lables.txt";
//    Kmeans k(5000,784,10,10,X_file,y_file);
//    k.solve();
//    k.accuracy();

    // test toy data
    string X_file="./data/toydata/X.txt";
    string y_file="./data/toydata/lables.txt";
    Kmeans k(5000,784,10,10,X_file,y_file);
    k.solve();
    k.accuracy();
}