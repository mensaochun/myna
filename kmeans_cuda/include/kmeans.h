//
// Created by pi on 2/7/18.
//

#ifndef KMEANS_CXX_KMEANS_H
#define KMEANS_CXX_KMEANS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>

#define random(x) (rand()%x) //create int in [0,x)

using std::vector
using std::string

class Kmeans {
private:
    int N; //num of samples
    int f; //num of features
    int k; //k clusters
    vector<vector<double>> X; //N*f mat
    vector<vector<double>> centers;//k*f mat
    vector<vector<double>> distances;//N*k mat


public:
    Kmeans(int N, int f, int k, string file_path);

    void read_data(string file_path);

    bool is_repeat(vector<int> vec, int val, int bound);

    vector<int> gen_random_center_indexes(int k, int N);

    void init_centers();
    // compute the distance between k centers
    vector<double> get_distance();
    void get_euclidean(const vector<double> &vec1,const vector<double> &vec2);
    void get_all_distances();


    ~Kmeans();


};


Kmeans::Kmeans(int N, int f, int k, string file_path) {
    this->N = N;
    this->f = f;
    this->k = k;
    this->X = vector(this->N, vector<double>(this->f, 0.0));
    this->centers(this->k, vector<double>(this->f, 0.0));
    this->distances(this->N, vector<double>(this->k, 0.0));
    this->read_data(file_path);
}

void Kmeans::read_data(string file_path) {
    std::fstream f;
    f.open(file_path);
    // ensure f is opened rightly.
    if (f) {
        for (int i = 0; i < this->N; i++) {
            for (int j = 0; j < this->f; j++) {
                f >> (this->X)[i][j];
            }
        }
    } else {
        std::cout << "Read file error!" << std::endl;
    }
    f.close();
}

//TODO: it is better to init vector using pointer.
bool Kmeans::is_repeat(vector<int> vec, int val, int bound) {
    //note bound is zero-based index
    for (int i = 0; i < bound + 1; i++) {
        if (val == vec[i]) {
            return true;
        }
    }
    return false;
}

vector<int> Kmeans::gen_random_center_indexes(int k, int N) {
    // gen random vector
    vector<int> random_center_indexes;
    srand((unsigned) time(NULL));
    for (int i = 0; i < k; i++) {
        int random_val = random(N);
        if (i != 1 && this->is_repeat(random_center_indexes, random_val, i - 1)) {
            i--;
        } else {
            random_center_indexes.push_back(random_val);
        }
    }
    return random_center_indexes;
}

void Kmeans::init_centers() {
    vector<int> random_center_indexes = this->gen_random_center_indexes(this->k, this->N);
    int i=0;
    for (auto iter = random_center_indexes.begin(); iter != random_center_indexes.end(); iter++) {
        this->centers[i]=this->X[*iter];
        i++;
    }
}
double Kmeans::get_euclidean(const vector<double> &vec1,const vector<double> &vec2){
    double d=0.0;
    for(auto iter=vec1.begin();iter!=vec1.end();iter++){
        d+=pow((vec1[*iter]-vec2[*iter]),2);
    }
    return d;
}

void Kmeans::get_distances(const vector<double> &vec){
    for(auto )
        for(auto iter=this->centers.begin();iter!=this->centers.end();iter++){

        }

}

Kmeans::~Kmeans() {

}

#endif //KMEANS_CXX_KMEANS_H
