
#ifndef CNN_BLOB_H
#define CNN_BLOB_H

#include <vector>
#include <armadillo>
#include <iostream>
#include <assert.h>
using namespace std;
using namespace arma;

enum FILLTYPE {
	DEFAULT = 1,
	ZEROS = 2,
	ONES = 3,
	RANDN = 4,
	RANDU = 5,
};

class Blob {
public:
	//构造函数
	Blob(int numSamples, int height, int width, int numChannels, FILLTYPE filltype = FILLTYPE::DEFAULT);
	Blob(vector<int> shape, FILLTYPE filltype = FILLTYPE::DEFAULT);
	~Blob() {};

	//运算符重载
	//Blob operator+(Blob &A);
	cube& operator[](const int &i);
	Blob& operator=(double num);
	friend Blob operator+(Blob &A, const double &num);
	friend Blob operator+(const double &num, Blob &A);
	friend Blob operator+(Blob &A, Blob &B);
	friend Blob operator-(Blob &A, const double &num);
	friend Blob operator-(const double &num, Blob &A);
	friend Blob operator-(Blob &A, Blob &B);
	friend Blob operator*(Blob &A, double num);
	friend Blob operator*(const double &num, Blob &A);
	friend Blob operator*(Blob &A, Blob &B);
	friend Blob operator/(Blob &A, const double &num);//element-wise divide
	friend Blob operator/(const double &num, Blob &A);
	friend Blob operator/(Blob &A, Blob &B);



	// getter
	int getNumSamples() const;
	int getNumChannels() const;
	int getWidth() const;
	int getHeight() const;
	vector<int> getShape() const;
	vector<cube> getData() const;

	// printer
	void print();
private:
	int numSamples;
	int numChannels;
	int height;
	int width;

	vector<cube> data;

	//private function
	void fill(int numSamples, int height, int width, int numChannels, FILLTYPE filltype = FILLTYPE::DEFAULT);


};


Blob operator+(Blob &A, const double &num);
Blob operator+(const double &num, Blob &A);
Blob operator+(Blob &A, Blob &B);
Blob operator-(Blob &A, const double &num);
Blob operator-(const double &num, Blob &A);
Blob operator-(Blob &A, Blob &B);
Blob operator*(Blob &A, double num);
Blob operator*(const double &num, Blob &A);
Blob operator*(Blob &A, Blob &B);
Blob operator/(Blob &A, const double &num);
Blob operator/(const double &num, Blob &A);
Blob operator/(Blob &A, Blob &B);

#endif //CNN_BLOB_H