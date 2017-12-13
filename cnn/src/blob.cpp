#include "blob.h"

//构造函数
Blob::Blob(int numSamples, int height, int width, int numChannels, FILLTYPE filltype) : numSamples(
	numSamples), height(height), width(width), numChannels(numChannels) {
	arma_rng::set_seed_random();
	this->fill(numSamples, height, width, numChannels, filltype);
}

Blob::Blob(vector<int> shape, FILLTYPE filltype) : numSamples(shape[0]), height(shape[1]), width(shape[2]),
numChannels(shape[3]) {
	arma_rng::set_seed_random();
	this->fill(numSamples, height, width, numChannels, filltype);
}

//initialize blob
void Blob::fill(int numSamples, int height, int width, int numChannels, FILLTYPE filltype) {
	if (filltype == FILLTYPE::DEFAULT) {
		this->data = vector<cube>(numSamples, cube(height, width, numChannels));
	}
	else if (filltype == FILLTYPE::ZEROS) {
		this->data = vector<cube>(numSamples, cube(height, width, numChannels, fill::zeros));
	}
	else if (filltype == FILLTYPE::ONES) {
		this->data = vector<cube>(numSamples, cube(height, width, numChannels, fill::ones));
	}
	else if (filltype == FILLTYPE::RANDU) {
		for (int i = 0; i < this->numSamples; i++) {
			this->data.push_back(cube(height, width, numChannels, fill::randu));
		}

	}
	else if (filltype == FILLTYPE::RANDN) {
		for (int i = 0; i < this->numSamples; i++) {
			this->data.push_back(cube(height, width, numChannels, fill::randn));
		}
	}
}

//
Blob Blob::pad(int pad,double val) {
	Blob out(this->numSamples, this->height + pad * 2, this->width+pad*2, this->numChannels);
	out = val;
	for (int n = 0;n< numSamples;n++) {
		for (int c = 0;c < numChannels;c++) {
			for (int h=0;h < height;h++) {
				for (int w=0;w < width;w++) {
					out[n](h + pad, w + pad, c) = this->data[n](h, w, c);
				}
			}
		}
	}
	return out;
}

//getter
int Blob::getNumSamples() const {
	return this->numSamples;
}

int Blob::getNumChannels() const {
	return this->numChannels;
}

int Blob::getWidth() const {
	return this->width;
}

int Blob::getHeight() const {
	return this->height;
}


vector<int> Blob::getShape() const {
	vector<int> shape{ this->numSamples, this->numChannels, this->height, this->width };
	return shape;
}

vector<cube> Blob::getData() const {
	return this->data;
}

//运算符重载
Blob& Blob::operator=(double num) {
	for (int i = 0;i<numSamples;i++) {
		(*this)[i].fill(num);
	}
	return *this;
}
/*
Blob Blob::operator+(Blob &A) {
	Blob out(this->getShape());
	for (int i = 0; i < A.getNumSamples(); i++) {
		out[i] = this->data[i] + A[i];
	}
	return out;
}*/

cube& Blob::operator[](const int &i) {
	return this->data[i];
}

Blob operator+(Blob &A, const double &num) {
	Blob out(A.getShape(),FILLTYPE::ZEROS);
	int N = A.getNumSamples();
	for (int i = 0; i < N; i++) {
		cube temp = A[i] + num;
		out[i] = temp;
		cube cubbe = out[i];
	}
	return out;
}

Blob operator+(const double &num, Blob &A) {
	Blob out(A.getShape(), FILLTYPE::ZEROS);
	int N = A.getNumSamples();
	for (int i = 0; i < N; i++) {
		out[i] = A[i] + num;
	}
	return out;
}
Blob operator+(Blob &A, Blob &B) {
	Blob out(A.getShape(),FILLTYPE::ONES);
	int N = A.getNumSamples();
	for (int i = 0;i < N;i++) {
		out[i] = A[i] + B[i];
	}
	return out;
}

Blob operator-(Blob &A, const double &num) {
	Blob out(A.getShape(), FILLTYPE::ZEROS);
	int N = A.getNumSamples();
	for (int i = 0; i < N; i++) {
		out[i] = A[i] - num;
	}
	return out;
}

Blob operator-(const double &num, Blob &A) {
	Blob out(A.getShape(), FILLTYPE::ZEROS);
	int N = A.getNumSamples();
	for (int i = 0; i < N; i++) {
		out[i] = num - A[i];
	}
	return out;
}

Blob operator-(Blob &A, Blob &B) {
	assert(A.getShape() == B.getShape());
	Blob out(A.getShape(), FILLTYPE::ZEROS);
	int N = A.getNumSamples();
	for (int i = 0; i < N; i++) {
		out[i] = A[i] - B[i];
	}
	return out;
}

Blob operator*(Blob &A, double num) {
	Blob out(A.getShape(), FILLTYPE::ZEROS);
	for (int i = 0;i<A.numSamples;i++) {
		out[i] = (A[i])*num;
	}
	return out;
}
Blob operator*(const double &num, Blob &A) {
	Blob out(A.getShape(), FILLTYPE::ZEROS);
	for (int i = 0;i<A.numSamples;i++) {
		out[i] = (A[i])*num;
	}
	return out;
}
Blob operator*(Blob &A, Blob &B) {
	assert(A.getShape() == B.getShape());
	Blob out(A.getShape(), FILLTYPE::ZEROS);
	for (int i = 0;i<A.numSamples;i++) {
		out[i] = A[i] % B[i];
	}
	return out;
}
Blob operator/(Blob &A, const double &num) {
	Blob out(A.getShape(), FILLTYPE::ZEROS);
	for (int i = 0;i<A.numSamples;i++) {
		out[i] = A[i] / num;
	}
	return out;
}
Blob operator/(const double &num, Blob &A) {
	Blob out(A.getShape(), FILLTYPE::ZEROS);
	for (int i = 0;i<A.numSamples;i++) {
		out[i] = A[i] / num;
	}
	return out;
}
Blob operator/(Blob &A, Blob &B) {
	assert(A.getShape() != B.getShape());
	Blob out(A.getShape());
	for (int i = 0;i<A.numSamples;i++) {
		out[i] = A[i] / B[i];
	}
	return out;
}


// printer
void Blob::print() {
	for (int i = 0; i < (this->getNumSamples()); i++) {
		vector<cube> data = this->getData();
		cout << "sample " << i << " ===============begin=================" << endl;
		cout << data[i];
		cout << "sample " << i << " ================end==================" << endl;
	}
}