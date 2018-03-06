/* 
 * Created by yourenchun.
 * Date:20180302.
*/

#ifndef NODE_H
#define NODE_H
#include"connection.h"
#include <vector>
using std::vector;
class Node {
private:
	int layerIdx;
	int nodeIdx;
	vector<Connection> preConns;
	vector<Connection> nextConns;d
	double output;
	double delta;
public:
	Node();
	Node(int layerIdx,int nodeIdx);
	void addPreConn();
	void addNextConn();
	void calOutput();
	void calHiddenDelta();
	void calOutputDelta();
	
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

void Node::addPreConn() {
	pre
}
void Node::addNextConn() {
}
void Node::calOutput() {

}
void Node::calHiddenDelta() {

}
void Node::calOutputDelta() {

}

#endif //NODE_H