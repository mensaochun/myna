//
// Created by yourenchun on 2/8/18.
//

#ifndef MAT_MAT_H
#define MAT_MAT_H

#define MATTEMPLATE template<typename T>

#include <iostream>
enum INITTYPE {
	NONE,
	ZEROS,
	ONES,
	RANDOMS
};

MATTEMPLATE
class Mat {
private:
    int cols;
    int rows;
    T **data;

public:
	Mat(int rows, int cols, INITTYPE type = INITTYPE::ZEROS);
	~Mat();
	T* operator[](int i);
	Mat<T> operator+(const Mat<T> &A);
	// TODO: const pointer?
	const T* Mat<T>::operator[](int i) const;
};


#endif //MAT_MAT_H
