/*!
*  Copyright (c) 2015 by hgaolbb
* \file blob.hpp
* \brief
*/

#ifndef MINI_NET_BLOB_HPP_
#define MINI_NET_BLOB_HPP_

#include <armadillo>
#include <vector>
#include <assert.h>
#include <iostream>
#include <cstdio>
#include <memory>

using std::vector;
using std::shared_ptr;
using namespace arma;

namespace mini_net {

enum FillType {
    TNONE = 0,
    TONES = 1,
    TZEROS = 2,
    TRANDU = 3,
    TRANDN = 4,
    TDEFAULT = 5
};

class Blob {

public:
    Blob() : N_(0), C_(0), H_(0), W_(0) {
        arma_rng::set_seed_random();
    }
    explicit Blob(const int n, const int c, const int h, const int w, int type = TDEFAULT);
    explicit Blob(const vector<int>& shape, int type = TDEFAULT);
    explicit Blob(int seed, const vector<int>& shape, int type = TDEFAULT);
    ~Blob() {}

    // need set shape later sometimes, like in test.hpp func[calcNumGradientBlob]
    void setShape(vector<int>& shape);
    cube& operator[] (int i);
    Blob& operator= (double num);

    friend Blob operator+(Blob& A, double num);
    friend Blob operator+(double num, Blob& A);
    friend Blob operator+(Blob& A, Blob& B);
    friend Blob operator-(Blob& A, double num);
    friend Blob operator-(double num, Blob& A);
    friend Blob operator-(Blob& A, Blob& B);
    friend Blob operator*(Blob& A, double num);
    friend Blob operator*(double num, Blob& A);
    friend Blob operator*(Blob& A, Blob& B);
    friend Blob operator/(Blob& A, double num);
    friend Blob operator/(double num, Blob& A);
    friend Blob operator/(Blob& A, Blob& B);

    Blob& operator+=(const double num);
    Blob& operator-=(const double num);
    Blob& operator*=(const double num);
    Blob& operator/=(const double num);

    // return [N,C,H,W]
    vector<int> size();

    inline int get_N() {
        return N_;
    }
    inline int get_C() {
        return C_;
    }
    inline int get_H() {
        return H_;
    }
    inline int get_W() {
        return W_;
    }

    // return data_
    vector<cube>& get_data();

    //@brief: reshape [N,C,H,W] to [N,C*H*W]
    mat reshape();

    /*! Element wise operation */
    // sum of all element in Blob
    double sum();
    /*! sum number of element*/
    double numElement();
    /*! element wise operation, if element value is smaller than val, then set it equals to val */
    Blob max(double val);
    /*! element wise operation, change data_ */
    void maxIn(double val);
    /*! element wise operation, change data_, if e = e < val ? 1 : 0; */
    void smallerIn(double val);
    /*! element wise operation, change data_, if e = e > val ? 1 : 0; */
    void biggerIn(double val);
    /*! element wise operation, return absolute value*/
    Blob abs();
    /*! sub Blob, return [lo, hi) */
    Blob subBlob(int lo, int hi);

    /*! find the max value in the blob */
    double maxVal();

    Blob pad(int p, double val = 0);
    Blob dePad(int p);
    /*! print Blob */
    void print(std::string s = "");

private:
    void _init(int n, int c, int h, int w, int type);

private:
    int N_;
    int C_;
    int H_;
    int W_;
    vector<cube> data_;
};

// operation
Blob operator+(Blob& A, double num);
Blob operator+(double num, Blob& A);
Blob operator+(Blob& A, Blob& B);
Blob operator-(Blob& A, double num);
Blob operator-(double num, Blob& A);
Blob operator-(Blob& A, Blob& B);
Blob operator*(Blob& A, double num);
Blob operator*(double num, Blob& A);
Blob operator*(Blob& A, Blob& B);
Blob operator/(Blob& A, double num);
Blob operator/(double num, Blob& A);
Blob operator/(Blob& A, Blob& B);

// convertion
void mat2Blob(mat& mA, shared_ptr<Blob>& out, int c, int h, int w);
void mat2Blob(mat& mA, shared_ptr<Blob>& out, const vector<int>& sz);

/*! \brief other math operation */
Blob sqrt(Blob& A);
/*! \brief prob */
double prob(Blob& Y, Blob& p);
/*! \brief element compare */
Blob compare(Blob& A, Blob& B);

} // namespace MiniNet

#endif // MINI_NET_BLOB_
