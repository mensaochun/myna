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


DecisionTree::DecisionTree(string dataFile) {
    // Read data from file.
    vector<vector<string>> dataTable;
	this->readFile(dataFile, dataTable);

    // Init trainSamples and trainLabels
    for(int i=1;i<dataTable.size();i++){
        this->trainLabels.push_back(dataTable[i][this->numFeatures-1]);
        vector<string> sample=this->dataTable[i];
        sample.pop_back();
        this->trainSamples.push_back(sample);
    }
    // Init some parameters.
    this->numFeatures = this->trainSamples[0].size(); // equal to the number of the columns.
    this->numSamples = this->trainSamples.size();// substact 1 because first row is not a sample.

    // Get all classes of data.
    // ref: https://blog.csdn.net/HE19930303/article/details/50579996
    this->classes=this->trainLabels;
    sort(this->classes.begin(),this->classes.end());
    this->classes.erase(unique(this->classes.begin(),this->classes.end()),this->classes.end());

    // Init table information
    this->featureNames = dataTable[0];
    this->featureNames.pop_back();
    for (int j = 0; j < this->numFeatures; j++) {
        string featureName = featureNames[j];
		this->featureIndexes[featureName] = j;
        vector<string> values;
        for (int i = 0; i < this->numSamples; i++) {
            values.push_back(this->trainSamples[i][j]);
        }
        sort(values.begin(),values.end());
        values.erase(unique(values.begin(),values.end()),values.end());
        this->tableInfo[featureName] = values;
    }

	// init rootNode
	for (int i = 0;i < this->numSamples;i++) {
		this->rootNode->sampleIdxes.push_back(i);
	}
	this->rootNode->features = this->featureNames;

}

DecisionTree::~DecisionTree() {

}

string DecisionTree::getSampleLabel(int sampleIdx) {
    return this->trainLabels[sampleIdx];
}

Node *DecisionTree::buildTree(Node *node) {
	/*
	To build a decision tree.
	1.is the node pure? if so, return it.
	2.determine the split feature corresponding to entropy.

	*/
    if (this->isPure(node)) {
        node->isLeaf = true;
        node->label = this->getSampleLabel(node->sampleIdxes[0]);
        return node;
    }
	node->isLeaf = false;
    string splitFeature = this->getSplitFeature(node);
    // for child node, remove the father's splitFeature.
    vector<string> subFeatures=node->features;
    auto iter=find(node->features.begin(),node->features.end(),splitFeature);
    subFeatures.erase(iter);
    // for child node, get new sample indexes.
    
    vector<string> values=this->tableInfo[splitFeature];
	// create children.
    for (int i=0;i<values.size();i++){
		Node *newNode = new Node;
		vector<int> subSampleIdxes;
		for (int j = 0;j < node->sampleIdxes.size();j++) {
			int idx = this->featureIndexes[values[i]];
			if (this->dataTable[j][idx]==values[i]) {
				subSampleIdxes.push_back(idx);
			}
		}
		newNode->sampleIdxes = subSampleIdxes;
		newNode->features = subFeatures;
		newNode->value = values[i];
		node->children.push_back(newNode);
    }
	return node;
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
    // sampleIdxes is 0-based.
    vector<int> sampleIdxes = node->sampleIdxes;
    string firstSampleLabel = this->trainLabels[sampleIdxes[0]];
    for (int i = 1; i < sampleIdxes.size(); i++) {
        if (this->trainLabels[sampleIdxes[i]]!= firstSampleLabel) {
            return false;
        }
    }
    return true;
}

void DecisionTree::createTree() {
	this->rootNode=this->buildTree(this->rootNode);
}