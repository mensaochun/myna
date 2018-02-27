//
// Created by yourenchun on 2/27/18.
//

#ifndef PERCEPTRON_PERCEPTRON_H
#define PERCEPTRON_PERCEPTRON_H

#include <vector>

using std::vector;

void getTraingData(vector<vector<double>> &X, vector<int> &Y);

void testPerceptron();

class Perceptron {
private:
    //data
    vector<vector<double>> X;
    vector<int> Y;
    int numFeatures;
    //model params
    vector<double> weights;
    double bias;
    //train params
    double learningRate;
    int iters;

    int (*activator)(double);

public:
    Perceptron(vector<vector<double>> X, vector<int> Y, int iters, double learningRate, int numFeatures);

    ~Perceptron();

    int predict(vector<double> x);

    void updataWeights(vector<double> x, int y);

    int stepFunc(double x);

    void train();

    void print();

};

#endif //PERCEPTRON_PERCEPTRON_H
