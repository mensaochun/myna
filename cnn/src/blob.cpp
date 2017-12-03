//
// Created by mensaochun on 12/2/17.
//

#include "../include/blob.h"

Blob::Blob(int numSamples, int numChannels, int height, int width) : numSamples(numSamples), numChannels(numChannels),
                                                                     height(height), width(width) {
    this->data = vector<cube>(numSamples, cube(height, width, numChannels, fill::ones));

}

int Blob::get_numSamples() {
    return this->numSamples;
}

vector<cube> Blob::getData() {
    return this->data;
}

//friend ostream operator<<(ostream &out, Blob &A) {
//    for (int i = 0; i < A.get_numSamples(); i++) {
//        vector<cube> data = A.getData();
//        out << "sample i:" << data[i];
//        return out;
//    }
//
//}

void Blob::print(){
    for(int i=0;i<(this->get_numSamples());i++){
        vector<cube> data=this->getData();
        cout<<"sample "<<i<<" ===============begin================="<<endl;
        cout<<data[i];
        cout<<"sample "<<i<<" ================end=================="<<endl;
    }
}
