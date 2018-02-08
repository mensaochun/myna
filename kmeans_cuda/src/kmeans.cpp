//
// Created by yourenchun on 2/7/18.
//

#include "../include/kmeans.h"

// note the function must not return the reference.
vector<double> operator+(const vector<double> &a, const vector<double> &b) {
    vector<double> c;
    for (int i = 0; i < a.size(); i++) {
        c.push_back(a[i] + b[i]);
    }
    return c;
}

vector<double> operator/(const vector<double> &vec, const double &val) {
    vector<double> vec2;
    for (int i = 0; i < vec.size(); i++) {
        vec2.push_back(vec[i]);
    }
    return vec2;
}

Kmeans::Kmeans(int N, int f, int k, int num_iters, string X_file_path, string y_file_path) {
    this->N = N;
    this->f = f;
    this->k = k;
    this->num_iters = num_iters;
    this->num_objs_cluster = vector<int>(this->k, 0);//num of objections in every cluster

    this->X = vector<vector<double>>(this->N, vector<double>(this->f, 0.0));
    this->y = vector<int>(this->N, 0);
    this->centers = vector<vector<double>>(this->k, vector<double>(this->f, 0.0));
    this->distances = vector<vector<double>>(this->N, vector<double>(this->k, 0.0));
    this->pre_lables = vector<int>(this->N, 0);
    this->read_data(X_file_path, y_file_path);
}

void Kmeans::read_data(string X_file_path, string y_file_path) {
    std::fstream f_X, f_y;
    f_X.open(X_file_path);
    // ensure f is opened rightly.
    std::cout<<"Begin read X data..."<<std::endl;
    if (f_X) {
        for (int i = 0; i < this->N; i++) {
            for (int j = 0; j < this->f; j++) {
                f_X >> (this->X)[i][j];
            }
        }
    } else {
        std::cout << "Read file error!" << std::endl;
    }
    f_X.close();

    std::cout<<"Begin read y data..."<<std::endl;
    f_y.open(y_file_path);
    // ensure f is opened rightly.
    if (f_y) {
        for (int i = 0; i < this->N; i++) {
            f_y >> (this->y)[i];
        }
    } else {
        std::cout << "Read file error!" << std::endl;
    }
    f_y.close();
    std::cout<<"Read data done!"<<std::endl;
}

//TODO: it is better to init vector using pointer.
bool Kmeans::is_repeat(const vector<int> &vec, const int &val, const int &bound) {
    //note bound is zero-based index
    for (int i = 0; i < bound + 1; i++) {
        if (val == vec[i]) {
            return true;
        }
    }
    return false;
}

vector<int> Kmeans::gen_random_center_indexes(const int &k, const int &N) {
    // gen random vector
    vector<int> random_center_indexes;
    srand((unsigned) time(NULL));
    for (int i = 0; i < k; i++) {
        int random_val = random(N);
        if (i != 1 && this->is_repeat(random_center_indexes, random_val, i - 1)) {
            i--;
        } else {
            random_center_indexes.push_back(random_val);
        }
    }
    return random_center_indexes;
}

void Kmeans::init_centers() {
    vector<int> random_center_indexes = this->gen_random_center_indexes(this->k, this->N);
    int i = 0;
    for (auto iter = random_center_indexes.begin(); iter != random_center_indexes.end(); iter++) {
        this->centers[i] = this->X[*iter];
        i++;
    }
}

double Kmeans::get_euclidean(const vector<double> &vec1, const vector<double> &vec2) {
    double d = 0.0;
    for (auto iter = vec1.begin(); iter != vec1.end(); iter++) {
        d += pow((vec1[*iter] - vec2[*iter]), 2);
    }
    return d;
}

void Kmeans::get_all_distances() {
    // not good to use iter.
    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->k; j++) {
            this->distances[i][j] = this->get_euclidean(this->X[i], this->centers[j]);
        }
    }
}

void Kmeans::get_lables() {
    for (int i = 0; i < this->N; i++) {
        vector<double>::iterator min = std::min_element(std::begin(this->distances[i]), std::end(this->distances[i]));
        this->pre_lables[i] = std::distance(std::begin(this->distances[i]), min);
    }
}

void Kmeans::reset_centers() {
    // reset centers to zero.
    this->centers = vector<vector<double>>(this->k, vector<double>(this->f, 0));
    for (int i = 0; i < this->N; i++) {
        this->centers[this->pre_lables[i]] = this->X[i] + centers[this->pre_lables[i]];
        this->num_objs_cluster[this->pre_lables[i]]++;
    }
    for (int i = 0; i < k; i++) {
        this->centers[i] = this->centers[i] / this->num_objs_cluster[i];
    }
}

void Kmeans::solve() {
    for (int i = 0; i < num_iters; i++) {
        std::cout<<"Iteration:"<<i<<std::endl;
        if (i == 0) {
            this->init_centers();
            this->get_all_distances();
            this->get_lables();
        } else {
            this->reset_centers();
            this->get_all_distances();
            this->get_lables();
        }
    }
    std::cout<<"Solving done!"<<std::endl;
}

double Kmeans::accuracy(){
    double count=0;
    for(int i=0;i<this->N;i++){
        if(this->pre_lables[i]==this->y[i]){
            count++;
        }
    }
    double accuracy=count/this->N;
    std::cout<<"Accuracy is "<<accuracy<<std::endl;
    return accuracy;
}
Kmeans::~Kmeans() {

}