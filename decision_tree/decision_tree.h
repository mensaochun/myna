//
// Created by yourenchun on 4/11/18.
//

#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
using std::vector;

struct Node{
    bool isLeaf;
    string splitFeature; // feature of this node to be splitted.
    string value; // value of the father node's splitFeature
    vector<Node> children;
    string label; // only used in leaf

};

class DecisionTree{
private:
    Node *rootNode;
    vector<vector<string>>  dataTable;
private:
    DecisionTree();
    ~DecisionTree();
    void readFile(string dataFile);
};
#endif //DECISION_TREE_H
