//
// Created by pi on 2/5/18.
//

#ifndef KNN_KNN_H
#define KNN_KNN_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <map>
#include <assert.h>
class KNN {
private:
    // reference matrix rows and cols
    int N;
    int num_train;
    int num_features;
    int num_test;
    // select k nearest neighbors
    int k;
    // reference data, here represent it by name train
    double **train_X;
    int *train_lable;// int indexes
    // test data
    double **test_X;
    int *test_lable;

public:
    KNN(int N, int num_features, double train_ratio, int k, std::string file_path);
    ~KNN();
    // read data from txt file and split it for reference and test data
    bool prepare_data(std::string file_path);
    void normalize_data();
    double* compute_distance(double *test_x);
    int inference_one(int *sort_lables);
    double inference_all();
    void show_data(std::string type);
    int* bubble_sort(double *distances);

};

#endif //KNN_KNN_H
