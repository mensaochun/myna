#include <iostream>
//#include "decision_tree.h"
//int main() {
//    cout<<"hello-----------------------------------------------------------------------";
//    DecisionTree dt("E:\\c++\\myna\\decision_tree\\data\\train.dat");
////    dt.printStrTable(dt.dataTable);
//    vector<string> vec=dt.dataTable[0];
//
//    for(int i=0;i<200;i++){
//        for (int j=0;j<vec.size();j++) {
////        cout.setf(ios::left);
//            cout  << vec[j] << " ";
//        }
//        cout << endl;
//
//    }
//
//    cout<<"hello-----------------------------------------------------------------------";
////    system( "PAUSE ");
//
//}
#include <vector>
using  namespace std;
int main(){
    vector<string> vec;
    vec.push_back("aaa");
    vec.push_back("bbb");
    vec.push_back("ccc");
    for(int i=0;i<200;i++){
        cout<<endl;
        cout<<i<<" ";
        for(int j=0;j<3;j++){
            cout<<vec[j]<<" ";
        }
    }
}