//#include <vector>
//#include <iostream>
//#include <armadillo>
#include "./include/blob.h"
using namespace std;
using std::vector;
int main(){
    Blob a=Blob(3,2,2,2);
    a.print();
    Blob b=Blob(3,2,3,4);
    (a+b).print();

}