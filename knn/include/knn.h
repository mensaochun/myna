//
// Created by pi on 2/5/18.
//

#ifndef KNN_KNN_H
#define KNN_KNN_H

#include <iostream>
#include <fstream>
#include <math.h>
class KNN {
private:
    int cols;
    int rows;
    int k;
    double **train_X;
    char *train_lable;

    bool read_data(std::string file_path);


public:
    KNN(int rows, int cols, std::string file_path);
    ~KNN();
    void compute_distance(double *test_x, double *distances);
    void show_data();
    void bubble_sort(double *distances,char *sort_lable);
    void show_result();
};

#endif //KNN_KNN_H
