//
// Created by pi on 2/5/18.
//
#include "../include/knn.h"

bool KNN::read_data(std::string file_path) {
    std::ifstream f;
    f.open(file_path);
    if (f) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                f >> (this->train_X)[i][j];
            }
            f >> this->train_lable[i];
        }
        return true;

    } else {
        std::cout << "Read file error!" << std::endl;
        return false;
    }

}

void KNN::compute_distance(double *test_x, double *distances) {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            distances[i] += pow((this->train_X[i][j] - test_x[j]), 2);
        }
    }

}

void KNN::show_data() {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << this->train_X[i][j] << " ";
        }
        std::cout << this->train_lable[i] << std::endl;
    }
}


KNN::KNN(int rows, int cols, std::string file_path) {
    this->rows = rows;
    this->cols = cols;
    this->train_X = new double *[rows];
    for (int i = 0; i < this->rows; i++) {
        this->train_X[i] = new double[this->cols];
    }
    this->train_lable = new char[this->rows];
    this->read_data(file_path);
}

void KNN::bubble_sort(double *distances, char *sort_lable) {
    for (int i = 0; i < this->rows; i++) {
        sort_lable[i]=this->train_lable[i];
    }
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->rows - i - 1; j++)
            if (distances[j] > distances[j + 1]) {
                double temp = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp;
                char temp_char = sort_lable[j];
                sort_lable[j] = sort_lable[j + 1];
                sort_lable[j + 1] = temp_char;

            }
    }
};

void KNN::show_result(){
    double test_x[]={3,0};
    double distances[12];
    this->compute_distance(test_x,distances);
    char sort_lable[12];
    this->bubble_sort(distances,sort_lable);
    for (int i=0;i<12;i++){
        std::cout<<"distance "<<distances[i]<<" label "<<sort_lable[i]<<std::endl;
    }
}

KNN::~KNN() {
    for (int i = 0; i < this->rows; i++) {
        delete[](this->train_X[i]);
    }
    delete this->train_lable;
    std::cout << "Delete data..." << std::endl;
}
