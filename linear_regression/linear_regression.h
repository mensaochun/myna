//
// Created by yourenchun on 2/27/18.
//

#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>

using std::vector;

void getTraingData(vector<vector<double>> &X, vector<int> &Y);

void testLinearRegression();

class LinearRegression {
private:
    //data
    vector<vector<double>> X;
    vector<double> Y;
    int numFeatures;
    //model params
    vector<double> weights;
    //train params
    double learningRate;
    int iters;

public:
	LinearRegression(vector<vector<double>> X, vector<double> Y, int iters, double learningRate, int numFeatures);

    ~LinearRegression();

    double predict(vector<double> x);

    void sgd(vector<double> x, double y);

	void bgd();

    void train_sgd();

	void train_bgd();

    void print();

};

#endif //LINEAR_REGRESSION_H
