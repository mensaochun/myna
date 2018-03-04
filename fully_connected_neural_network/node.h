/* 
 * Created by yourenchun.
 * Date:20180302.
*/

class Node {
protected:
	int layerIdx;
	int nodeIdx;
public:
	Node(int layerIdx,int nodeIdx);
	// pure virtual function.
	// virtual double output() =0;
};
Node::Node(int layerIdx, int nodeIdx){
	this->layerIdx = layerIdx;
	this->nodeIdx = nodeIdx;
}

class HiddenNode :public Node {
private:
	List preNodes;
	List nextNodes;
	double out;
	double delta;
public:
	HiddenNode();
	template<typename T> void addPreConn(const T &node);
	template<typename T> void addNextConn(const T &node);
};