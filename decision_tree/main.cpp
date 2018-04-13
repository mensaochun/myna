#include <iostream>
//#include "decision_tree.h"
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int main() {

    vector<string> vec;
    vec.push_back("aa");
    vec.push_back("bb");
    std::cout<<std::count(vec.begin(),vec.end(),"bb");
}
