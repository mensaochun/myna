//
// Created by yourenchun on 4/11/18.
//

#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <map>
#include <math.h>
#include <algorithm>
using namespace std;
using std::vector;

struct Node{
    bool isLeaf;
    vector<string> features;
    vector<int> sampleIdxes;

    string splitFeature; // feature of this node to be splitted.
    string value; // value of the father node's splitFeature
    vector<Node> children;
    string label; // only used in leaf

};

class DecisionTree{
private:
    Node *rootNode;
    int numFeatures;
    int numSamples;
    map<string,vector<string>> tableInfo;
    vector<string> classes;
    vector<vector<string>>  dataTable;
public:
    void printStrVec(vector<string> vec);
    void printStrTable(vector<vector<string>> strTabel);
    void readFile(string dataFile,vector<vector<string>> &dataTable);
public:
    DecisionTree(string trainDataFile);
    bool isPure(Node *node);
    string getSampleLabel(int sampleIdx);
    string getSplitFeature(Node *node);
    ~DecisionTree();
    Node* buildTree(Node *node);

};
#endif //DECISION_TREE_H
