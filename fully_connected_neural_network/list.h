/* 
 * Created by yourenchun.
 * Date:20180302.
*/
/********************************ListNode****************************/
#include "node.h"
template<typename T>
class ListNode {
public:
	T1 data;
	ListNode<T> *next;

	ListNode();
	ListNode(T data);
};

template<typename T>
ListNode<T>::ListNode() {
	// not init data.
	this->next = NULL;
}

template<typename T>
ListNode<T>::ListNode(T data) {
	this->data = data;
	this->next = NULL;
}

/********************************List****************************/
class List {
private:
	ListNode<Node> *head;
	int length;
public:
	List();
	~List();
	template<typename T> void append(const T &data);
};


List::List() {
	// Head has no data
	this->head = new ListNode<Node>();
	this->length = 0;
}
template<typename T> void List::append(const T &data){
	// read the last node
	ListNode<T> *temp = this->head;
	while (temp->next) {
		temp = temp->next;
	}
	ListNode<T> newNode=new ListNode<T>(data);
	temp->next = &newNode;
	this->length++;
}