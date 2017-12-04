//
// Created by mensaochun on 12/2/17.
//

#include "../include/blob.h"

Blob::Blob(int numSamples, int numChannels, int height, int width) : numSamples(numSamples), numChannels(numChannels),
                                                                     height(height), width(width) {
    this->data = vector<cube>(numSamples, cube(height, width, numChannels, fill::zeros));

}
Blob::Blob(vector<int> shape) {
    this->data = vector<cube>(shape[0], cube(shape[1], shape[2], shape[3],fill::zeros));
}

int Blob::getNumSamples() const {
    return this->numSamples;
}

int Blob::getNumChannels() const {
    return this->numChannels;
}

int Blob::getWidth() const {
    return this->width;
}

int Blob::getHeight() const {
    return this->height;
}



vector<int> Blob::getShape() const {
    vector<int> shape{this->numSamples, this->numChannels, this->height, this->width};
    return shape;
}

vector<cube> Blob::getData() const {
    return this->data;
}

//运算符重载

Blob Blob::operator+(const Blob &A) {
    Blob out(this->getShape());
    for (int i = 0; i < A.getNumSamples(); i++) {
        out[i] = this->data[i] + A[i];
    }
    return out;
}

cube Blob::operator[](const int &i){
    return this->data[i];
}

Blob operator+(const Blob &A,const double &i){
    Blob out(A.getShape());
    int N=A.getNumSamples();
    for(int i=0;i<N;i++){
        out[i]=
    }
    cube I(A.numChannels,A.height,A.width,(fill::ones)*i);

}

//friend ostream operator<<(ostream &out, Blob &A) {
//    for (int i = 0; i < A.get_numSamples(); i++) {
//        vector<cube> data = A.getData();
//        out << "sample i:" << data[i];
//        return out;
//    }
//
//}

void Blob::print() {
    for (int i = 0; i < (this->getNumSamples()); i++) {
        vector<cube> data = this->getData();
        cout << "sample " << i << " ===============begin=================" << endl;
        cout << data[i];
        cout << "sample " << i << " ================end==================" << endl;
    }
}
