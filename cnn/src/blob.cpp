#include "../include/blob.h"

//constructor
Blob::Blob(const int &numSamples, const int &height, const int &width, const int &numChannels, FILLTYPE filltype)
        : numSamples(
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
void Blob::fill(const int &numSamples, const int &height, const int &width, const int &numChannels, FILLTYPE filltype) {
    if (filltype == FILLTYPE::DEFAULT) {
        this->data = vector<cube>(numSamples, cube(height, width, numChannels));
    } else if (filltype == FILLTYPE::ZEROS) {
        this->data = vector<cube>(numSamples, cube(height, width, numChannels, fill::zeros));
    } else if (filltype == FILLTYPE::ONES) {
        this->data = vector<cube>(numSamples, cube(height, width, numChannels, fill::ones));
    } else if (filltype == FILLTYPE::RANDU) {
        for (int i = 0; i < this->numSamples; i++) {
            this->data.push_back(cube(height, width, numChannels, fill::randu));
        }

    } else if (filltype == FILLTYPE::RANDN) {
        for (int i = 0; i < this->numSamples; i++) {
            this->data.push_back(cube(height, width, numChannels, fill::randn));
        }
    }
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
    vector<int> shape{this->numSamples, this->numChannels, this->height, this->width};
    return shape;
}

vector<cube> Blob::getData() const {
    return this->data;
}

// overloaded operator
Blob &Blob::operator=(double num) {
    for (int i = 0; i < numSamples; i++) {
        (*this)[i].fill(num);
    }
    return *this;
}

cube &Blob::operator[](const int &i) {
    return this->data[i];
}

Blob operator+(Blob &A, const double &num) {
    Blob out(A.getShape(), FILLTYPE::ZEROS);
    int N = A.getNumSamples();
    for (int i = 0; i < N; i++) {
        out[i] = A[i] + num;
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
    Blob out(A.getShape(), FILLTYPE::ONES);
    int N = A.getNumSamples();
    for (int i = 0; i < N; i++) {
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
    for (int i = 0; i < A.numSamples; i++) {
        out[i] = (A[i]) * num;
    }
    return out;
}

Blob operator*(const double &num, Blob &A) {
    Blob out(A.getShape(), FILLTYPE::ZEROS);
    for (int i = 0; i < A.numSamples; i++) {
        out[i] = (A[i]) * num;
    }
    return out;
}

Blob operator*(Blob &A, Blob &B) {
    assert(A.getShape() == B.getShape());
    Blob out(A.getShape(), FILLTYPE::ZEROS);
    for (int i = 0; i < A.numSamples; i++) {
        out[i] = A[i] % B[i];
    }
    return out;
}

Blob operator/(Blob &A, const double &num) {
    Blob out(A.getShape(), FILLTYPE::ZEROS);
    for (int i = 0; i < A.numSamples; i++) {
        out[i] = A[i] / num;
    }
    return out;
}

Blob operator/(const double &num, Blob &A) {
    Blob out(A.getShape(), FILLTYPE::ZEROS);
    for (int i = 0; i < A.numSamples; i++) {
        out[i] = A[i] / num;
    }
    return out;
}

Blob operator/(Blob &A, Blob &B) {
    assert(A.getShape() == B.getShape());
    Blob out(A.getShape());
    for (int i = 0; i < A.numSamples; i++) {
        out[i] = A[i] / B[i];
    }
    return out;
}

// calculation operators
double Blob::sum() const {
    assert(!this->data.empty());
    double s = 0;
    for (int i = 0; i < this->numSamples; i++) {
        s += arma::accu(this->data[i]);
    }
    return s;
}

double Blob::getNumElements() const {
    return this->numSamples * this->numChannels * this->width * this->height;
}

Blob Blob::max(const double &val) {
    assert(!this->data.empty());
    Blob out = *this;
    for (int i = 0; i < this->numSamples; i++) {
        out[i].transform([val](double e) { return e < val ? val : e; });
    }
    return out;
}

void Blob::maxIn(const double &val) {
    assert(!this->data.empty());
    for (int i = 0; i < this->numSamples; i++) {
        this->data[i].transform([val](double e) { return e < val ? val : e; });
    }
    return;
}

void Blob::smallerIn(const double &val) {
    assert(!this->data.empty());
    for (int i = 0; i < this->numSamples; i++) {
        this->data[i].transform([val](double e) { return e < val ? 1 : 0; });
    }
    return;
}

void Blob::biggerIn(const double &val) {
    assert(!this->data.empty());
    for (int i = 0; i < this->numSamples; i++) {
        this->data[i].transform([val](double e) { return e > val ? 1 : 0; });
    }
    return;
}

Blob Blob::abs() {
    Blob out(this->getShape(), FILLTYPE::ZEROS);
    for (int i = 0; i < this->numSamples; i++) {
        //fabs?
        out[i].transform([](double e) { return fabs(e);});
    }
}

Blob Blob::subBlob(int low, int high){
    assert(low<high);
    Blob out((high-low),height,width,numChannels,FILLTYPE::ZEROS);
    for(int i=0;i<(high-low);i++){
        out[i]=(*this)[low];
    }
    return out;
}

double Blob::maxValue(){
    assert(!this->data.empty());
    double maxValue=(*this)[0].max();
    for(int i=0;i<numSamples;i++){
        double maxValue_i=(*this)[i].max();
        if(maxValue_i>maxValue){
            maxValue=maxValue_i;
        }
    }
    return maxValue;
}



// printer
void Blob::print() {
    for (int i = 0; i < (this->getNumSamples()); i++) {
        vector<cube> data = this->getData();
        cout << "sample" << "[" << i << "]:" << endl;
        cout << data[i];
        cout << endl;
    }
}