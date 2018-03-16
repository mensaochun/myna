#include "./mat/mat.h"
using namespace myna;
int main(){
    Mat<int> M(2,3,Fill::ONES);
    M.print();
    Mat<int> S=M;
    S.print();

}