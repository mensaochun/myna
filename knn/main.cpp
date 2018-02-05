#include "include/knn.h"

int main() {
    std::string file_path = "/home/pi/stone/c++/knn/data/data.txt";
    KNN knn(12, 2, file_path);
    knn.show_result();
//    knn.show_data();
//    double test[2];
//    test[0]=1;
//    test[1]=1;
////    double dis[12];
//    double *dis=new double[12];
//    knn.compute_distance(test,dis);
//    for(int i=0;i<12;i++){
//        std::cout<<dis[i]<<std::endl;
//    }
//    delete []dis;

//    double a[]={3,5,2,1,3,1,1,1,1,1,1,1};
//    knn.bubble_sort(a);
//    for(int i=0;i<12;i++){
//        std::cout<<a[i];
//    }


}