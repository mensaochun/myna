//
// Created by yourenchun on 4/11/18.
//


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
        while (row.length() != 0 && row.find(',') != string::npos) {
            int loc = row.find_first_of(',');
            tempVec.push_back(row.substr(0, loc));
            row.erase(0, loc + 1);
        }
        tempVec.push_back(row);
        dataTable.push_back(tempVec);
    }
    inputFile.close();

}

void DecisionTree::printStrVec(vector<string> vec) {
    for (vector<string>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
        cout.setf(ios::left);
        cout << setw(10) << *iter << " ";
    }
    cout << endl;
}

void DecisionTree::printStrTable(vector<vector<string>> strTable) {
    int i = 0;
    for (vector<vector<string>>::iterator iter = strTable.begin(); iter != strTable.end(); iter++) {
        cout.setf(ios::left);
        cout << setw(3) << i << " ";
        printStrVec(*iter);
        i++;
    }
}


DecisionTree::DecisionTree(string trainDataFile) {
    readFile(trainDataFile, dataTable);
    this->numFeatures = dataTable[0].size(); // equal to the number of the columns.
    this->numSamples = dataTable.size() - 1;// substact 1 because first row is not a sample.
    this->classes.push_back(dataTable[1][numFeatures - 1]);
    // to get all classes of data.
    for (int i = 1; i < dataTable.size() - 1; i++) {
        string label = this->dataTable[i][numFeatures - 1];
        if (this->classes.back() != label) {
            this->classes.push_back(label);
        }
    }

    // init table information
    vector<string> featureNames = this->dataTable[0];
    for (int i = 0; i < this->numFeatures; i++) {
        string featureName = featureNames[i];
        vector<string> values;
        for (int j = 1; j < this->numSamples - 1; j++) {
            bool isExist = count(values.begin(), values.end(), this->dataTable[j][i]);
            if (!isExist) {
                values.push_back(this->dataTable[j][i]);
            }
        }
        this->tableInfo[featureName] = values;
    }
}

DecisionTree::~DecisionTree() {

}

string DecisionTree::getSampleLabel(int sampleIdx) {
    return this->dataTable[sampleIdx][this->numFeatures - 1];
}

Node *DecisionTree::buildTree(Node *node) {
    if (this->isPure(node)) {
        node->isLeaf = true;
        node->label = this->getSampleLabel(node->sampleIdxes[0]);
        return node;
    }
    string splitFeature = this->getSplitFeature(node);
    // for child node, remove the splitFeature.
    vector<string> subFeatures=node->features;
    auto iter=find(node->features.begin(),node->features.end(),splitFeature);
    subFeatures.erase(iter);
    // for child node, get new sample indexes.
    vector<string> subSampleIdxes;
    vector<string> values=this->tableInfo[splitFeature];
    for (int i=0;i<this->tableInfo[splitFeature].size();i++){

    }
}

string DecisionTree::getSplitFeature(Node *node) {
    vector<string> features = node->features;
    vector<int> sampleIdxes = node->sampleIdxes;
    vector<double> entropies;
    // for every feature, compute entropy.
    for (int i = 0; i < features.size(); i++) {
        // for every feature, count the number of the samples of every class.
        map<string, double> countMap;
        for (int j = 0; j < sampleIdxes.size(); j++) {
            string label = this->getSampleLabel(sampleIdxes[j]);
            if (countMap.find(label) == countMap.end()) {
                countMap[label] = 1.0;
            } else {
                countMap[label] += 1.0;
            }
        }
        // compute the feature's entropy
        double entropy = 0.0;
        int num = sampleIdxes.size();
        for (map<string, double>::iterator iter = countMap.begin(); iter != countMap.end(); iter++) {
            pair<string, double> pair_ = *iter;
            double p = pair_.second / num;
            entropy += -log(p) * p;
        }
        entropies.push_back(entropy);
    }
    // get the feature which has the max entropy.
    vector<double>::iterator maxPosIter = min_element(entropies.begin(), entropies.end());// return a iterator.
    int minPosIdx = maxPosIter - entropies.begin();//TODO: it is equal to index?
    string splitFeature = features[minPosIdx];
    return splitFeature;
}

bool DecisionTree::isPure(Node *node) {
    // sampleIdxes is 1-based.
    vector<int> sampleIdxes = node->sampleIdxes;
    string firstSampleClass = this->dataTable[sampleIdxes[0]][this->numFeatures - 1];
    for (int i = 1; i < sampleIdxes.size(); i++) {
        if (this->dataTable[sampleIdxes[i]][this->numFeatures - 1] != firstSampleClass) {
            return false;
        }
    }
    return true;
}