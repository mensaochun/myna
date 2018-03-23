//
// Created by pi on 3/22/18.
//

#ifndef FC_VEC_TEST_VEC_H
#define FC_VEC_TEST_VEC_H

#include "vector.hpp"

using namespace myna;
void test(){
//    Vector<double> a(3);
//    Vector<double> b(5,Fill::ONES);
//    Vector<double> c(5,Fill::ZEROS);
    Vector<double> d(5,Fill::RANDOM);
//    a.print();
//    b.print();
//    c.print();
    d.pushBack(100);
    d.pushBack(101);
    d.print();


}

#endif //FC_VEC_TEST_VEC_H
