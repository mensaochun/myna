//
// Created by yourenchun on 2/27/18.
//
#include "linear_regression.h"
#include <iostream>


void getTraingData(vector<vector<double>> &X, vector<double> &Y) {
    X = {vector<double>{5}, vector<double>{3}, vector<double>{8}, vector<double>{1.4},vector<double>{10.1} };
    Y = vector<double>{ 5500, 2300, 7600, 1800, 11400 };
}

void testLinearRegression() {
    vector<vector<double>> X;
    vector<double> Y;
    getTraingData(X, Y);
	LinearRegression lr = LinearRegression(X, Y, 10, 0.01, 1);
    lr.train_sgd();
    lr.print();
    std::cout << std::endl;
    std::cout << "Start Test!" << std::endl;
    //Note: need to add 1 to sample x's back.
    std::cout << "Work 3.4 years, monthly salary= " << lr.predict(vector<double>{3.4,1}) << std::endl;
    std::cout << "Work 15 years, monthly salary = " << lr.predict(vector<double>{15,1}) << std::endl;
    std::cout << "Work 1.5 years, monthly salary = " << lr.predict(vector<double>{1.5,1}) << std::endl;
    std::cout << "Work 6.3 years, monthly salary = " << lr.predict(vector<double>{6.3,1}) << std::endl;
	std::cout << "Test Done!" << std::endl;
}

LinearRegression::LinearRegression(vector<vector<double>> X, vector<double> Y, int iters, double learningRate, int numFeatures) {
    this->X = X;
	for (int i = 0;i < X.size();i++) {
		this->X[i].push_back(1.0);
	}
    this->Y = Y;
    this->learningRate = learningRate;
    this->numFeatures = numFeatures;
    this->weights = vector<double>(this->numFeatures+1);
    this->iters = iters;
}

LinearRegression::~LinearRegression() {

}

double LinearRegression::predict(vector<double> x) {
    x.push_back(1.0);
    double out=0.0;
    for (int i = 0; i < x.size(); i++) {
        out += this->weights[i] * x[i];
    }
    return out;
}

void LinearRegression::sgd(vector<double> x, double y) {
    // x is one train sample, and y is its label.
    double p = this->predict(x);
    double delta = y - p;
    for (int i = 0; i < x.size(); i++) {
        this->weights[i] += learningRate * delta * x[i];
    }
}
void LinearRegression::bgd() {
    //TODO: it exists bugs
    // x is one train sample, and y is its label.
    vector<double> out(this->numFeatures+1);
    for(int i=0;i<this->X.size();i++){
        double delta = this->Y[i] - this->predict(this->X[i]);
        for(int j=0;j<(this->numFeatures+1);j++) {
            out[j] += delta *X[i][j];
        }
    }
    for(int k=0;k<(this->numFeatures+1);k++){
        this->weights[k] += learningRate * out[k];
    }
}

void LinearRegression::train_sgd() {
	std::cout << "Start sgd training!" << std::endl;
    for (int iter = 0; iter < this->iters; iter++) {
		std::cout << "Iteration " << iter << std::endl;
		// TODO: it is not actually stochastic.
		for (int i = 0;i < this->X.size();i++) {
			this->sgd(this->X[i], this->Y[i]);
		}
	}
	std::cout << "Training done!" << std::endl;
}

void LinearRegression::train_bgd() {
    std::cout << "Start bgd training!" << std::endl;
    for (int iter = 0; iter < this->iters; iter++) {
        std::cout << "Iteration " << iter << std::endl;
        this->bgd();
    }
    std::cout << "Training done!" << std::endl;
}

void LinearRegression::print() {
    std::cout << "weights:[";
    for (int i = 0; i < this->weights.size()-1; i++) {
        std::cout << this->weights[i] << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "biases:" << this->weights.back()<<std::endl;
}

