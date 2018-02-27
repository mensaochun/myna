//
// Created by yourenchun on 2/27/18.
//
#include "perceptron.h"
#include <iostream>


void getTraingData(vector<vector<double>> &X, vector<int> &Y) {
    X = {vector<double>{1, 1}, vector<double>{0, 0}, vector<double>{1, 0}, vector<double>{0, 1}};
    Y = vector<int>{1, 0, 0, 0};
}

void testPerceptron() {
    vector<vector<double>> X;
    vector<int> Y;
    getTraingData(X, Y);
    Perceptron p = Perceptron(X, Y, 100, 0.1, 2);
    p.train();
    p.print();
    std::cout << std::endl;
    std::cout << "Test" << std::endl;
    std::cout << "1 and 1 = " << p.predict(vector<double>{1, 1}) << std::endl;
    std::cout << "0 and 0 = " << p.predict(vector<double>{0, 0}) << std::endl;
    std::cout << "1 and 0 = " << p.predict(vector<double>{1, 0}) << std::endl;
    std::cout << "0 and 1 = " << p.predict(vector<double>{0, 1}) << std::endl;
}

Perceptron::Perceptron(vector<vector<double>> X, vector<int> Y, int iters, double learningRate, int numFeatures) {
    this->X = X;
    this->Y = Y;
    this->learningRate = learningRate;
    this->numFeatures = numFeatures;
    this->weights = vector<double>(this->numFeatures);
    this->bias = 0.0;
    this->iters = iters;
}

Perceptron::~Perceptron() {

}

int Perceptron::stepFunc(double x) {
    return (x > 0 ? 1 : 0);
}

int Perceptron::predict(vector<double> x) {
    double z;
    for (int i = 0; i < x.size(); i++) {
        z += this->weights[i] * x[i];
    }
    z += this->bias;
    int a = stepFunc(z);
    return a;
}

void Perceptron::updataWeights(vector<double> x, int y) {
    // x is one train sample, and y is its label.
    int p = this->predict(x);
    int delta = y - p;
    for (int i = 0; i < x.size(); i++) {
        this->weights[i] += learningRate * delta * x[i];
    }
    this->bias += learningRate * delta;
}


void Perceptron::train() {
    for (int i = 0; i < this->iters; i++) {
        std::cout << "Iteration " << i << std::endl;
        for (int j = 0; j < this->weights.size(); j++) {
            this->updataWeights(this->X[j], this->Y[j]);
        }
    }
    std::cout << "Training is done!" << std::endl;
}

void Perceptron::print() {
    std::cout << "weights:[";
    for (int i = 0; i < this->weights.size(); i++) {
        std::cout << this->weights[i] << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "biases:" << this->bias;
}

