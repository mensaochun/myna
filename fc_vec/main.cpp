//#include "./networkComponent/test_net.hpp"
//using namespace myna;
#include <iostream>
class A{
private:
    int output;
public:
    A(int output){
        this->output=output;
    }
    int & getOutput(){
        return output;
    }
};

class B{
private:
    int *input;
public:
    void setInput(int &a){
        input=a;
    }
};


int main(){
    A a(1);
    B b;
    b.setInput(a.getOutput());
    std::cout<<"";

}