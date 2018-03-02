//
// Created by yourenchun on 2/27/18.
//
#include "perceptron.h"
#include <iostream>


void getTraingData(vector<vector<double>> &X, vector<double> &Y) {
    X = {vector<double>{1, 1}, vector<double>{0, 0}, vector<double>{1, 0}, vector<double>{0, 1}};
    Y = vector<double>{1, 0, 0, 0};
}

void testPerceptron() {
    vector<vector<double>> X;
    vector<double> Y;
    getTraingData(X, Y);
    Perceptron p = Perceptron(X, Y, 10, 0.1, 2);
    p.train();
    p.print();
    std::cout << std::endl;
    std::cout << "Start Test!" << std::endl;
    std::cout << "1 and 1 = " << p.predict(vector<double>{1, 1, 1}) << std::endl;
    std::cout << "0 and 0 = " << p.predict(vector<double>{0, 0, 1}) << std::endl;
    std::cout << "1 and 0 = " << p.predict(vector<double>{1, 0, 1}) << std::endl;
    std::cout << "0 and 1 = " << p.predict(vector<double>{0, 1, 1}) << std::endl;
    std::cout << "Test Done!" << std::endl;
}

Perceptron::Perceptron(vector<vector<double>> X, vector<double> Y, int iters, double learningRate, int numFeatures) {
    this->X = X;
    // add 1 for bias.
    for (int i = 0; i < X.size(); i++) {
        this->X[i].push_back(1.0);
    }
    this->Y = Y;
    this->learningRate = learningRate;
    this->numFeatures = numFeatures;
    this->weights = vector<double>(this->numFeatures + 1);
    this->iters = iters;
}

Perceptron::~Perceptron() {

}

double Perceptron::stepFunc(double x) {
    return (x > 0 ? 1 : 0);
}

double Perceptron::predict(vector<double> x) {
    double z = 0.0;
    for (int i = 0; i < x.size(); i++) {
        z += this->weights[i] * x[i];
    }
    double a = this->stepFunc(z);
    return a;
}

void Perceptron::updateWeights(vector<double> x, double y) {
    // x is one train sample, and y is its label.
    double p = this->predict(x);
    double delta = y - p;
    for (int i = 0; i < x.size(); i++) {
        this->weights[i] += learningRate * delta * x[i];
    }
}


void Perceptron::train() {
    std::cout << "Start training!" << std::endl;
    for (int iter = 0; iter < this->iters; iter++) {
        std::cout << "Iteration " << iter << std::endl;
        for (int i = 0; i < this->X.size(); i++) {
            this->updateWeights(this->X[i], this->Y[i]);
        }
    }
    std::cout << "Training done!" << std::endl;
}

void Perceptron::print() {
    std::cout << "weights:[";
    for (int i = 0; i < this->weights.size() - 1; i++) {
        std::cout << this->weights[i] << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "biases:" << this->weights.back() << std::endl;
}

