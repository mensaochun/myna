

#include "mat_vector.h"
struct _span{

};
int main() {
    Mat<int> A(2, 3, ONES);
    Mat<int> B(3, 4, ONES);
    Mat<int> C = A.matMul(B);
    C.print();
    Mat<int> D=C.subMat(span(0,1),span(2,3));
    D.print();
    return 0;

}