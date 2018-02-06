#include "include/knn.h"

int main() {
    /// toy example--------------------
//    std::string file_path = "/home/pi/stone/c++/knn/data/data.txt";
//    KNN knn(12, 2, 0.5, 10, file_path);
//    knn.show_data("train");
//    knn.show_data("test");
//    double test_x[2] = {3, 0};
//    double *distances = knn.compute_distance(test_x);
//    for (int i = 0; i < 6; i++) {
//        std::cout << distances[i] << std::endl;
//    }
//    std::cout << "lables sorted!" << std::endl;
//    int *sort_lables = knn.bubble_sort(distances);
//    for (int i = 0; i < 6; i++) {
//        std::cout << distances[i] << std::endl;
//    }
//
    /// halen example -------------
    std::string file_path = "/home/pi/stone/c++/knn/data/datingTestSet2.txt";
    KNN knn(1000, 3, 0.8, 10, file_path);
//    knn.show_data("train");
//    knn.show_data("test");
//    double test_x[3] = {40920,8.326976, 0.953952};
//    double *distances = knn.compute_distance(test_x);
//    for (int i = 0; i < 800; i++) {
//        std::cout << distances[i] << std::endl;
//    }
//    std::cout << "lables sorted：" << std::endl;
//    int *sort_lables = knn.bubble_sort(distances);
//    for (int i = 0; i < 800; i++) {
//        std::cout << distances[i] << std::endl;
//    }
//    for(int i=0;i<800;i++){
//        std::cout<<sort_lables[i]<<std::endl;
//    }
//    int result=knn.inference_one(sort_lables);
//    std::cout<<"result:"<<result<<std::endl;
//    knn.inference_all();


}