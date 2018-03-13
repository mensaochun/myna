/* 
 * Created by yourenchun.
 * Date:20180302.
*/

#ifndef NODE_H
#define NODE_H
#include<math.h>
#include"connection.h"
#include <vector>
using std::vector;

double sigmoid(double x) {
	double out=1.0 / (1.0 + exp(-x));
	return out;
}

class Node {
private:
	int layerIdx;
	int nodeIdx;
	vector<Connection> preConns;
	vector<Connection> nextConns;
	double output;
	double delta;
public:
	Node();
	Node(int layerIdx,int nodeIdx);
	void setOutput(double output);
	void addPreConn(const Connection &preConn);
	void addNextConn(const Connection &nextConn);
	double calOutput();
	void calHiddenDelta();
	void calOutputDelta();
	double getDelta();
	double getOutput();
	
};

Node::Node(){
	this->output = 0.0;
	this->delta = 0.0;
}
Node::Node(int layerIdx, int nodeIdx){
	this->layerIdx = layerIdx;
	this->nodeIdx = nodeIdx;
	this->output = 0.0;
	this->delta = 0.0;
}
void Node::setOutput(double output) {
	this->output = output;
}
void Node::addPreConn(const Connection &preConn) {
	this->preConns.push_back(preConn);
}
void Node::addNextConn(const Connection &nextConn) {
	this->nextConns.push_back(nextConn);
}
void Node::calOutput() {
	double out=0.0;
	for (int i = 0;i < this->preConns.size();i++) {
		out=preConns[i].getPreNode().getOutput())*(preConns[i].getWeight());
	}
	this->output = sigmoid(output);
}
void Node::calHiddenDelta() {
	double temp = 0.0;
	for (int i = 0;i < this->nextConns.size();i++) {
		temp+=(this->nextConns[i].getNextNode().getDelta())*(this->nextConns[i].getWeight());
	}
	this->delta = this->output*(1 - this->output)*temp;
}
void Node::calOutputDelta(double label) {
	this->delta=this->output*(1-this->output)(label-this->output)
}
double Node::getDelta() {
	return this->delta;
}
double Node::getOutput() {
	return this->output;
}


class ConstNode {
private:
	int layerIdx;
	int nodeIdx;
	vector<Node> nextConns;
	double output;
public:
	ConstNode(int nodeIdx,int layerIdx);
	void addNextConn();
	void calHiddenDelta();
};
ConstNode::ConstNode(int nodeIdx, int layerIdx) {
	this->layerIdx = layerIdx;
	this->nodeIdx = nodeIdx;
}

void ConstNode::addNextConn() {

}
void ConstNode::calHiddenDelta() {

}

#endif //NODE_H