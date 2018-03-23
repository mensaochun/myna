//
// Created by yourenchun on 3/22/18.
//

#ifndef FC_VEC_COMMON_H
#define FC_VEC_COMMON_H

#include <iostream>
namespace myna{
    // enum Fill-------------------------------
    enum Fill {
        NONE,
        ZEROS,
        ONES,
        RANDOM
    };

    // enum Axis-------------------------------
    enum Axis {
        ROW,
        COL,
        BOTH
    };

    // Span-------------------------------------
    struct SpanAll {
    };

    // random function
    template<typename T>
    T uniformRandom(T a, T b);

    class Span {
    public:
        int a;
        int b;
        static const SpanAll all;

        Span(int in_a, int in_b);

        Span(int in_a);
    };

    // span--------------------------------------
    Span::Span(int in_a) : a(in_a) {}

    Span::Span(int in_a, int in_b) : a(in_a), b(in_b) {}

    const SpanAll Span::all = SpanAll();

    // random------------------------------------
    template<typename T>
    T uniformRandom(T a, T b) {

        return (b - a) * rand() / T(RAND_MAX) + a;
    }


}


#endif //FC_VEC_COMMON_H
