//
// Created by yourenchun on 2/7/18.
//

#ifndef KMEANS_CXX_KMEANS_H
#define KMEANS_CXX_KMEANS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>
#include <algorithm>
#define random(x) (rand()%x) //create int in [0,x)

using std::vector;
using std::string;
vector<double>& operator+(const vector<double> &a, const vector<double> &b) {
	vector<double> c;
	for (int i = 0;i < a.size();i++) {
		c.push_back(a[i] + b[i]);
	}
	return c;
}

class Kmeans {
private:
    int N; //num of samples
    int f; //num of features
    int k; //k clusters
	int num_iters;
	
	vector<int> num_objs_cluster;//num of objections in every cluster
    vector<vector<double>> X; //N*f mat
    vector<vector<double>> centers;//k*f mat
    vector<vector<double>> distances;//N*k mat
	vector<int> lables;//N*1


public:
    Kmeans(int N, int f, int k, int num_iters,string file_path);

    void read_data(string file_path);

    bool is_repeat(const vector<int> &vec,const int &val, const int &bound);

    vector<int> gen_random_center_indexes(const int &k, const int &N);

    void init_centers();
    // compute the distance between k centers
    double get_euclidean(const vector<double> &vec1,const vector<double> &vec2);
    void get_all_distances();
	void get_lables();
	void reset_centers();
    
	void solve();
    ~Kmeans();
};


Kmeans::Kmeans(int N, int f, int k,int num_iters, string file_path) {
    this->N = N;
    this->f = f;
    this->k = k;
	this->num_iters = num_iters;
	this->num_objs_cluster=vector<int>(this->k,0);//num of objections in every cluster
	
    this->X = vector<vector<double>>(this->N, vector<double>(this->f, 0.0));
    this->centers= vector<vector<double>>(this->k, vector<double>(this->f, 0.0));
    this->distances= vector<vector<double>>(this->N, vector<double>(this->k, 0.0));
	this->lables = vector<int>(this->N, 0);
    this->read_data(file_path);
}

void Kmeans::read_data(string file_path) {
    std::fstream f;
    f.open(file_path);
    // ensure f is opened rightly.
    if (f) {
        for (int i = 0; i < this->N; i++) {
            for (int j = 0; j < this->f; j++) {
                f >> (this->X)[i][j];
            }
        }
    } else {
        std::cout << "Read file error!" << std::endl;
    }
    f.close();
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
    int i=0;
    for (auto iter = random_center_indexes.begin(); iter != random_center_indexes.end(); iter++) {
        this->centers[i]=this->X[*iter];
        i++;
    }
}
double Kmeans::get_euclidean(const vector<double> &vec1,const vector<double> &vec2){
    double d=0.0;
    for(auto iter=vec1.begin();iter!=vec1.end();iter++){
        d+=pow((vec1[*iter]-vec2[*iter]),2);
    }
    return d;
}

void Kmeans::get_all_distances(){
	// not good to use iter.
	for (int i = 0;i < this->N;i++) {
		for (int j = 0;j < this->k;j++) {
			this->distances[i][j] = this->get_euclidean(this->X[i], this->centers[j]);
		}
	}
}

void Kmeans::get_lables() {
	for (int i = 0;i < this->N;i++) {
		vector<double>::iterator min = std::min_element(std::begin(this->distances[i]), std::end(this->distances[i]));
		this->lables[i] =std::distance(std::begin(this->distances[i]),min);
	}
}

void Kmeans::reset_centers() {
	// reset centers to zero.
	this->centers = vector<vector<double>>(this->k, vector<double>(this->f, 0));
	for (int i = 0;i < this->N;i++) {
		this->centers[this->lables[i]]=this->X[i]+ centers[this->lables[i]];
		this->num_objs_cluster[this->lables[i]]++;
	}
	for (int i = 0;i < k;i++) {

	}
}
void Kmeans::solve() {
	for (int i = 0;i < num_iters;i++) {
		if (i == 0) {
			this->init_centers();
			this->get_all_distances();
			this->get_lables();
		}
		else {
			this->
		}
	}
}
Kmeans::~Kmeans() {

}

#endif //KMEANS_CXX_KMEANS_H
