/* 
 * Created by yourenchun.
 * Date:20180302.
*/
#ifndef CONNECTION_H
#define CONNECTION_H
#include"node.h"
#include<stdlib.h>//used for RAND_MAX
#include<time.h>//used for time()

double random(double a, double b) {
	srand((unsigned)time(NULL));//gen seed,need set everytime?
	double random = ((double)rand()) / (double)RAND_MAX;//generate [0,1],include 0 and 1?
	return a + random * (b - a);
}
class Connection {
private:
	Node preNode;
	Node nextNode;
	double weight;
	double gradient;
	void calGradient();
	
public:
	Connection(const Node &preNode, const Node &nextNode);
	~Connection();
	double getGradient();
	void updateWeight(double learningRate);
	Node getPreNode();
	Node getNextNode();
	double getWeight();
	
};

Connection::Connection(const Node &preNode, const Node &nextNode) {
	this->preNode = preNode;
	this->nextNode = nextNode;
	this->weight = random(0, 1);
	this->getGradient = 0.0;
}
Connection::~Connection() {

}

double Connection::getGradient() {
	return this->gradient;
}

void Connection::calGradient() {
	this->gradient = this->preNode.getDelta() * this->nextNode.getOutput();
}

void Connection::updateWeight(double learningRate) {
	this->calGradient();
	this->weight += learningRate*this->getGradient;
}


Node Connection::getPreNode() {
	return this->preNode;
}
Node Connection::getNextNode() {
	return this->nextNode;
}
double Connection::getWeight() {
	return this->weight;
}


#endif CONNECTION_H
