//
// Created by pi on 2/5/18.
//
#include "../include/knn.h"

bool KNN::prepare_data(std::string file_path) {
    std::ifstream f;
    f.open(file_path);
    if (f) {
        for (int i = 0; i < this->num_train; i++) {
            for (int j = 0; j < this->num_features; j++) {
                f >> (this->train_X)[i][j];
            }
            f >> this->train_lable[i];
        }
        for (int i = 0; i < this->num_test; i++) {
            for (int j = 0; j < this->num_features; j++) {
                f >> (this->test_X)[i][j];
            }
            f >> this->test_lable[i];
        }
        return true;

    } else {
        std::cout << "Read file error!" << std::endl;
        return false;
    }

}

double *KNN::compute_distance(double *test_x) {
    double *distances = new double[this->num_train];

    for (int i = 0; i < this->num_train; i++) {
        distances[i] = 0;
        for (int j = 0; j < this->num_features; j++) {
            distances[i] += pow((this->train_X[i][j] - test_x[j]), 2);
        }
    }
    return distances;
}

double KNN::inference_all() {
    double true_count = 0;
    for (int i = 0; i < this->num_test; i++) {
        double *test_x = this->test_X[i];
        double *distances = this->compute_distance(test_x);
        int *sort_lables = this->bubble_sort(distances);
        int result = this->inference_one(sort_lables);
        if (result == this->test_lable[i]) {
            true_count++;
        }
        //TODO: this way can delete memory?
        delete[]distances;
        delete[]sort_lables;
    }
    double accuracy = true_count / this->num_test;
    std::cout << "true count：" << true_count << std::endl;
    std::cout << "Test accuracy:" << accuracy << std::endl;
    return accuracy;
}

int KNN::inference_one(int *sort_lables) {
    // note: lable's index is one-based!
    std::map<int, int> m;
    for (int i = 1; i < this->k + 1; i++) {
        m.insert(std::pair<int, int>(i, 0));
    }
    for (int j = 0; j < k; j++) {
        for (int i = 1; i < this->k + 1; i++) {
            if (sort_lables[j] == i) {
                m[i]++;
                continue;
            }
        }
    }
    int max_value = m[1];
    for (int i = 1; i < this->k; i++) {
        if (m[i + 1] > max_value) {
            max_value = m[i + 1];
        }
    }

    for (int i = 1; i < this->k + 1; i++) {
        if (m[i] == max_value) {
            return i;
        }
    }
}

void KNN::show_data(std::string type) {
    if (type == "train") {
        int count = 0;
        for (int i = 0; i < this->num_train; i++) {
            for (int j = 0; j < this->num_features; j++) {
                std::cout << this->train_X[i][j] << " ";
            }
            count++;
            std::cout << this->train_lable[i] << std::endl;
        }
        std::cout << "Total num of train data: " << count << std::endl;
    } else if (type == "test") {
        int count = 0;
        for (int i = 0; i < this->num_test; i++) {
            for (int j = 0; j < this->num_features; j++) {
                std::cout << this->test_X[i][j] << " ";
            }
            count++;
            std::cout << this->test_lable[i] << std::endl;
        }
        std::cout << "Total num of test data: " << count << std::endl;
    } else {
        assert("Input type is error! must be string train or test!");
    }

}


KNN::KNN(int N, int num_features, double train_ratio, int k, std::string file_path) {
    this->N = N;
    this->num_features = num_features;
    this->num_train = (int) (train_ratio * this->N);
    this->num_test = N - this->num_train;
    this->k = k;

    this->train_X = new double *[this->num_train];
    // init reference data
    for (int i = 0; i < this->num_train; i++) {
        this->train_X[i] = new double[this->num_features];
    }
    this->test_X = new double *[this->num_test];
    for (int i = 0; i < this->num_test; i++) {
        this->test_X[i] = new double[this->num_features];
    }
    this->train_lable = new int[this->num_train];
    this->test_lable = new int[this->num_train];
    this->prepare_data(file_path);
}

int *KNN::bubble_sort(double *distances) {
    // note that the distances is a array pointer, so after sorted, the distances are sorted.
    int *sort_lables = new int[this->num_train];
    for (int i = 0; i < this->num_train; i++) {
        sort_lables[i] = this->train_lable[i];
    }
    for (int i = 0; i < this->num_train; i++) {
        for (int j = 0; j < this->num_train - i - 1; j++)
            if (distances[j] > distances[j + 1]) {
                //sort the distances
                double temp = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp;
                // also sort the lables
                int temp_char = sort_lables[j];
                sort_lables[j] = sort_lables[j + 1];
                sort_lables[j + 1] = temp_char;

            }
    }
//    delete[]distances;
    return sort_lables;
};

void KNN::normalize_data() {
    double *norm=new double[this->num_features];
    for(int i=0;i<this->num_train;i++){
        for(int j=0;j<this->num_features;j++){

        }
    }
}

KNN::~KNN() {
    for (int i = 0; i < this->num_train; i++) {
        delete[](this->train_X[i]);
    }
    for (int i = 0; i < this->num_test; i++) {
        delete[](this->test_X[i]);
    }
    delete[](this->train_lable);
    delete[](this->test_lable);
    std::cout << "Delete data..." << std::endl;
}
