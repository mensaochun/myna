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
#include <string>
using namespace std;
using std::vector;

struct Node{
    bool isLeaf;
    vector<string> features;
    vector<int> sampleIdxes;
    string splitFeature; // feature of this node to be splitted.
    string value; // value of the father node's splitFeature
    vector<Node *> children;
    string label; // only used in leaf

};

class DecisionTree{
public:
    vector<vector<string>> trainSamples;
    vector<string> trainLabels;
    vector<string> featureNames;
    vector<string> classes;// all classes.
    int numFeatures;
    int numSamples;
	map<string, int> featureIndexes;
    map<string,vector<string>> tableInfo; // Key: feature name, value: a vector storing feature values.
    Node *rootNode;
public:
    void printStrVec(vector<string> vec);
    void printStrTable(vector<vector<string>> strTabel);
    void readFile(string dataFile,vector<vector<string>> &dataTable);
public:
    DecisionTree(string dataFile);
	~DecisionTree();
    bool isPure(Node *node); // Determine is the node filled with samples with same label.
    string getSampleLabel(int sampleIdx);
    string getSplitFeature(Node *node);
    Node* buildTree(Node *node);
	void createTree();

};
#endif //DECISION_TREE_H
