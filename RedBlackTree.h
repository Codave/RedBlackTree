#pragma once
#include"Except.h"

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

	void insert(const Comparable& x);

	typedef RedBlackNode<Comparable> Node;	//定义类型别名
//private:  为了测试，临时变成public
public:   
	Node* header;  //头指针
	Node* nullNode;	//空结点

	Node* current;	//当前结点
	Node* parent;	//父结点
	Node* grand;	//祖父结点
	Node* great;	//曾祖父结点

	void rotateWithLeftChild(Node*& k2) const;
	void rotateWithRightChild(Node*& k1) const;

	void doubleRotateWithLeftChild(Node*& k3) const;
	void doubleRotateWithRightChild(Node*& k1) const;
};

template<class Comparable>
class RedBlackNode {
public:	//为了测试，临时变为public
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
RedBlackTree<Comparable>::RedBlackTree(const Comparable& negInf) {	//红黑树的构造函数
	nullNode = new Node();
	nullNode->left = nullNode->right = nullNode;
	header = new Node(negInf);
	header->left = header->right = nullNode;
}

template<class Comparable>
RedBlackTree<Comparable>::~RedBlackTree() {	//红黑树的析构函数
	delete nullNode;
	delete header;
}
 
template<class Comparable>
void RedBlackTree<Comparable>::insert(const Comparable& x) {
	current = parent = grand = header;
	nullNode->element = x;		//	成员函数可以访问private数据

	while (current->element != x) {
  		great = grand;		grand = parent;		parent = current;
		current = x < current->element ? current->left : current->right;
	}

	if (current != nullNode) {
		throw DuplicateItemException();
	}

	current = new Node(x, nullNode, nullNode);
	if (x < parent->element) {
		parent->left = current;
	}
	else {
		parent->right = current;
	}

	//	自动平衡 -> 红黑树
}

template<class Comparable>
void RedBlackTree<Comparable>::rotateWithLeftChild(Node*& k2) const {	//右旋
	Node* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1; 
}

template<class Comparable>
void RedBlackTree<Comparable>::rotateWithRightChild(Node*& k1) const {	//左旋
	Node* k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1 = k2;
}

template<class Comparable>
void RedBlackTree<Comparable>::doubleRotateWithLeftChild(Node*& k3) const {

}

template<class Comparable>
void RedBlackTree<Comparable>::doubleRotateWithRightChild(Node*& k1) const {

}