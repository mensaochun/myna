//
// Created by yourenchun on 3/22/18.
//

#ifndef FC_VEC_VECTOR_H
#define FC_VEC_VECTOR_H

#include "common.hpp"

namespace myna {
    template<typename T>
    class Vector {
    private:
        const int interval = 200;
        int capacity;
        int size;
        T *data;
    private:
        void addCapacity();

    public:
        Vector();

        Vector(int n);

        Vector(int n, Fill fill);

        ~Vector();

//        void pushBack(const T &elem);

        void pushBack(const T elem);

        void print();


    };

    template<typename T>
    Vector<T>::Vector() {
        this->size=0;
        this->capacity=0;
        this->data = nullptr;
    }

    template<typename T>
    Vector<T>::Vector(int n) {
        this->size=n;
        this->capacity = n;
        this->data = new T[n];
    }

    template<typename T>
    Vector<T>::Vector(int n, Fill fill) {
        this->size = n;
        this->capacity = n;
        this->data = new T[n];
        if (fill == Fill::ONES) {
            for (int i = 0; i < this->size; i++) {
                this->data[i] = 1;
            }
        } else if (fill == Fill::ZEROS) {
            for (int i = 0; i < this->size; i++) {
                this->data[i] = 0;
            }
        } else if (fill == Fill::RANDOM) {
            for (int i = 0; i < this->size; i++) {
                this->data[i] = uniformRandom<T>(-1, 1);// only used for double type.
            }
        }
    }

    template<typename T>
    Vector<T>::~Vector() {
        if (this->data = nullptr) {
            return;
        } else {
            delete[]this->data;
        }
    }

    template<typename T>
    void Vector<T>::addCapacity() {
        // copy data, add capacity
        T *temp = this->data;
        this->data = new T[this->size + this->interval];
        this->capacity += this->interval;
        for (int i = 0; i < this->capacity; i++) {
            this->data[i] = temp[i];
        }
        delete[]temp;
    }

//    template<typename T>
//    void Vector<T>::pushBack(const T &elem) {
//        if (this->size < this->capacity) {
//            this->data[size] = elem;
//            this->size++;
//        } else {
//            this->addCapacity();
//            this->data[size] = elem;
//            this->size++;
//        }
//
//    }

    template<typename T>
    void Vector<T>::pushBack(const T elem) {
        if (this->size <this->capacity) {
            this->data[size] = elem;
            this->size++;
        } else {
            this->addCapacity();
            this->data[size] = elem;
            this->size++;
        }
    }
    template<typename T>
    void Vector<T>::print(){
        if(this->size>0){
            std::cout<<"Print vector:"<<std::endl;
            for(int i=0;i<this->size;i++){
                std::cout<<this->data[i]<<" ";
            }
            std::cout<<"\n\n";
        }else{
            std::cout<<"There is no data in the vector\n\n";
        }

    }
}

#endif //FC_VEC_VECTOR_H
