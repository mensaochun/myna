/* 
 * Created by yourenchun.
 * Date:20180302.
*/
#ifndef CONNECTION_H
#define CONNECTION_H
#include"node.h"
class Connection {
private:
	Node preNode;
	Node nextNode;
	double weight;
	double gradient;
	void calGradient();
public:
	Connection(Node preNode, Node nextNode);
	~Connection();
	void getGradient();
	void update_weight();

};

Connection::Connection(Node preNode,Node nextNode) {
	this->preNode = preNode;
	this->nextNode = nextNode;
}


void Connection::calGradient() {

}
#endif CONNECTION_H
