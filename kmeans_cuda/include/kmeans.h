//
// Created by yourenchun on 2/7/18.
//

#ifndef KMEANS_CXX_KMEANS_H
#define KMEANS_CXX_KMEANS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>
#include <algorithm>

#define random(x) (rand()%x) //create int in [0,x)

using std::vector;
using std::string;

// reload the normal operators.
vector<double> operator+(const vector<double> &a, const vector<double> &b);

vector<double> operator/(const vector<double> &vec, const double &val);

class Kmeans {
private:
    int N; //num of samples
    int f; //num of features
    int k; //k clusters
    int num_iters;

    vector<int> num_objs_cluster;//num of objections in every cluster
    vector<vector<double>> X; //N*f mat
    vector<int> y; //N*1
    vector<vector<double>> centers;//k*f mat
    vector<vector<double>> distances;//N*k mat
    vector<int> pre_lables;//N*1


public:
    Kmeans(int N, int f, int k, int num_iters, string X_file_path, string y_file_path);

    void read_data(string X_file_path, string y_file_path);

    bool is_repeat(const vector<int> &vec, const int &val, const int &bound);

    vector<int> gen_random_center_indexes(const int &k, const int &N);

    void init_centers();

    // compute the distance between k centers
    double get_euclidean(const vector<double> &vec1, const vector<double> &vec2);

    void get_all_distances();

    void get_lables();

    void reset_centers();

    void solve();

    double accuracy();

    ~Kmeans();
};

#endif //KMEANS_CXX_KMEANS_H
