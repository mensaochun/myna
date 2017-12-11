
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
    // constructors
    Blob(const int &numSamples, const int &height, const int &width, const int &numChannels, FILLTYPE filltype = FILLTYPE::DEFAULT);
    Blob(vector<int> shape, FILLTYPE filltype = FILLTYPE::DEFAULT);
    ~Blob() {};

    // operators reload
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

    // shape operator

    // calculation operator
    double sum() const;
    double getNumElements() const;

    //not change data
    Blob max(const double &val) ;
    void maxIn(const double &val);
    void smallerIn(const double &val);
    void biggerIn(const double &val);
    Blob abs(); //not change data
    Blob subBlob(int low, int high);
    double maxValue();



    // printer
    void print();
private:
    int numSamples;
    int numChannels;
    int height;
    int width;

    vector<cube> data;

    //private function
    void fill(const int &numSamples, const int &height, const int &width, const int &numChannels, FILLTYPE filltype = FILLTYPE::DEFAULT);
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