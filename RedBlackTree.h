#pragma once

template<class Comparable>
class RedBlackTree;

template<class Comparable>	//提前引用声明
class RedBlackNode;       

template<class Comparable>
class RedBlackTree {
public:
	RedBlackTree(const Comparable& negInf);	//红黑树的构造函数
	~RedBlackTree();	//红黑树的析构函数
	
	enum{RED,BLACK};

	typedef RedBlackNode<Comparable> Node;	//定义类型别名
private:
	Node* header;  //头指针
	Node* nullNode;	//空结点
};

template<class Comparable>
class RedBlackNode {

	Comparable		element;
	RedBlackNode*	left;
	RedBlackNode*	right;
	int				color;

	RedBlackNode(const Comparable& theElement = Comparable(),	//结点的构造函数，用初始化列表进行初始化
		RedBlackNode* lt = NULL,								//theElement用Comparable()默认初始化
		RedBlackNode* rt=NULL,
		int c=RedBlackTree<Comparable>::BLACK)
		:element(theElement),left(lt),right(rt),color(c){ }

	friend class RedBlackTree<Comparable>;	//声明RedBlackTree为类RedBlackNode的友元类
};

template<class Comparable>
RedBlackTree<Comparable>::RedBlackTree(const Comparable& negInf) {
	nullNode = new Node();
	nullNode->left = nullNode->right = nullNode;
	header = new Node(negInf);
	header->left = header->right = nullNode;
}

template<class Comparable>
RedBlackTree<Comparable>::~RedBlackTree() {
	delete nullNode;
	delete header;
}