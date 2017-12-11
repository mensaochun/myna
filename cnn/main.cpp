#include "./include/blob.h"

using namespace std;
using std::vector;

#include <armadillo>
using namespace arma;

int main() {
//    Blob a(1, 2, 3, 4, FILLTYPE::RANDN);
//    Blob b(1, 2, 3, 4, FILLTYPE::ONES);
//    Blob c=a.max(1);
//    c.print();
////    Blob c(1, 2, 3, 4, FILLTYPE::RANDN);
//    //Blob d(1, 2, 3, 4, FILLTYPE::RANDU);
//    //Blob e(1, 2, 3, 4);
//    //Blob sum_blob = a + b;
//    Blob c=0.1/b;
//    c.print();
//    double num = 3;
//    Blob numBlob = num+c;
//    numBlob.print();
    ////sum_blob.print();
    //numBlob.print();

    /*vector<int> vec{ 1,2,3,4,5 };
    for (int i = 0;i < vec.size();i++) {
        cout << vec[i];
    }
    for (int i = 0;i < vec.size();i++) {
        vec[i] = 3;
    }
    for (int i = 0;i < vec.size();i++) {
        cout << vec[i];
    }*/

    /*a.print();
    b.print();
    c.print();
    d.print();
    e.print();*/
    arma::cube a=randn<arma::cube>(2,3,3);
//    arma::max(a);


}