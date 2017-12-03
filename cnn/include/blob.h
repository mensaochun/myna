//
// Created by mensaochun on 12/2/17.
//

#ifndef CNN_BLOB_H
#define CNN_BLOB_H


#include <vector>
#include <armadillo>
#include <iostream>
using namespace std;
using std::vector;//vector 是命名空间吗？
using namespace arma;
class Blob{
public:
    Blob(int numSamples,int numChannels,int height,int width);
    ~Blob() = default;

    //运算符重载
//    Blob operator+(const Blob &A);
    int get_numSamples();
    vector<cube> getData();
    //Blob operator+(const Blob &A,const Blob &B);
//    friend ostream operator<<(ostream &out,Blob &A);
    void print();
private:
    int numSamples;
    int numChannels;
    int height;
    int width;

    vector<cube> data;


};
#endif //CNN_BLOB_H

