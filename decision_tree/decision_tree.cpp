//
// Created by yourenchun on 4/11/18.
//

#include "decision_tree.h"
void DecisionTree::readFile(string dataFile) {
    fstream inputFile;
    inputFile.open(dataFile.c_str());
    if(!inputFile){
        cerr<<"Open file error!";
        exit(-1);
    }
    string row;
    while(getline(inputFile,row)){
        int idx=row.find_first_of(",");
        dataTable[]
    }

}