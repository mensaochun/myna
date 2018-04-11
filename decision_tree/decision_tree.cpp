//
// Created by yourenchun on 4/11/18.
//

#include <iomanip>
#include "decision_tree.h"

void DecisionTree::readFile(string dataFile, vector<vector<string>> &dataTable) {
    fstream inputFile;
    inputFile.open(dataFile.c_str());
    if (!inputFile) {
        cerr << "Open file error!";
        exit(-1);
    }

    string row;
    while (getline(inputFile, row)) {
        vector<string> tempVec;
        while (row.length()!=0 && row.find(',') != string::npos) {
            int loc = row.find_first_of(',');
            tempVec.push_back(row.substr(0, loc));
            row.erase(0, loc + 1);
        }
        tempVec.push_back(row);
        dataTable.push_back(tempVec);
    }
    inputFile.close();

}
//
//void DecisionTree::printStrVec(vector<string> vec) {
//    for (vector<string>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
//        cout.setf(ios::left);
//        cout << setw(10) << *iter << " ";
//    }
//    cout << endl;
//}

void DecisionTree::printStrVec(vector<string> vec) {
    for (int i=0;i<vec.size();i++) {
//        cout.setf(ios::left);
        cout  << vec[i] << " ";
    }
    cout << endl;
}



void DecisionTree::printStrTable(vector<vector<string>> strTable) {
    int i=0;
    for (vector<vector<string>>::iterator iter = strTable.begin(); iter != strTable.end(); iter++) {
        cout.setf(ios::left);
        cout<<setw(3)<<i<<" ";
        printStrVec(*iter);
        i++;
    }
}


DecisionTree::DecisionTree(string trainDataFile) {
    readFile(trainDataFile, dataTable);
}

DecisionTree::~DecisionTree() {
    cout<<"done!";
}


void DecisionTree::buildTree(){

}