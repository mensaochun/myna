//
// Created by yourenchun on 2/27/18.
//

#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>

using std::vector;

void getTraingData(vector<vector<double>> &X, vector<double> &Y);

void testPerceptron();

class Perceptron {
private:
    //data
    vector<vector<double>> X;
    vector<double> Y;
    int numFeatures;
    //model params
    vector<double> weights;//include bias
    //train params
    double learningRate;
    int iters;

public:
    Perceptron(vector<vector<double>> X, vector<double> Y, int iters, double learningRate, int numFeatures);

    ~Perceptron();

    double stepFunc(double x);

    double predict(vector<double> x);

    void updateWeights(vector<double> x, double y);

    void train();

    void print();

};

#endif //PERCEPTRON_H
