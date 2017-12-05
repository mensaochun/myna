//#include <vector>
//#include <iostream>
//#include <armadillo>
#include "./include/blob.h"

using namespace std;
using std::vector;

#include <armadillo>
using namespace arma;

int main() {




//    double b=3.0;
//    Blob c = b-a;
//    c.print();


//    cout<<zeros+1;

//    Blob b=Blob(1,2,3,4);
//    b.print();
//    vector<int> a{3,2,3,4};
//    cout<<a[0];
    //Blob b=Blob(a,FILLTYPE::RANDN);
//    Blob b(1,2,3,4,FILLTYPE::RANDU);
//    b.print();
//    cube a=cube(1,2,3);
//    double b=1.0;
//    (a+b).print();
//    (cube(2,2,2,fill::randu)).print();
//    vector<int> data;

    //Blob +
//    Blob a(1,2,3,4);
//    Blob b(1,2,3,4);
//    double num;
//    (a+num).print();
//    (num+a).print();
//    (a+b).print();

    //Blob /
    Blob a(1,2,3,4,FILLTYPE::ONES);
    Blob b(1,2,3,4,FILLTYPE::ONES);
    Blob c(1,2,3,4);
    c=3.0;
    c.print();
    a.print();
//    b.print();
    Blob d=c-a;
    d.print();
//    double num=2.0;
//    (b/c).print();



}