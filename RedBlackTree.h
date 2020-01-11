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

	void rotateWithLeftChild(Node*& k2) const;	//右旋
	void rotateWithRightChild(Node*& k1) const;	//左旋

	void doubleRotateWithLeftChild(Node*& k3) const;	//右旋
	void doubleRotateWithRightChild(Node*& k1) const;	//左旋

	void handleReorient(const Comparable& item);
	RedBlackNode<Comparable>* rotate(const Comparable& item, Node* parent) const;  //其实返回值是Node*

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
	nullNode = new Node();	//空结点（NULL）
	nullNode->left = nullNode->right = nullNode;
	header = new Node(negInf);    //伪头结点
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

		if (current->left->color == RED && current->right->color == RED) {
			handleReorient(x);
		}
	}

	if (current != nullNode) {    //找到了相等的结点
		throw DuplicateItemException();
	}

	current = new Node(x, nullNode, nullNode);
	if (x < parent->element) {
		parent->left = current;
	}
	else {
		parent->right = current;
	}
	handleReorient(x);


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
void RedBlackTree<Comparable>::doubleRotateWithLeftChild(Node*& k3) const {//先左旋后右旋
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

template<class Comparable>
void RedBlackTree<Comparable>::doubleRotateWithRightChild(Node*& k1) const {//先右旋后左旋
	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}

template<class Comparable>
inline void RedBlackTree<Comparable>::handleReorient(const Comparable& item) {
	//变色
	current->color = RED;
	current->left->color = BLACK;
	current->right->color = BLACK;

	if (parent->color == RED) {
		grand->color = RED;
		if (item < grand->element != item < parent->element) {
			parent = rotate(item, grand);
		}
		current = rotate(item, great);
		current->color = BLACK;
	}
	header->right->color = BLACK;

	//单旋转

	//双旋转
}

template<class Comparable>
RedBlackNode<Comparable>* RedBlackTree<Comparable>::rotate(const Comparable& item, Node* theParent) const{
	if (item < theParent->element) {
		item < theParent->left->element ?
			rotateWithLeftChild(theParent->left) :
			rotateWithRightChild(theParent->left);
		return theParent->left;
	}
	else {
		item < theParent->right->element ?
			rotateWithLeftChild(theParent->right) :
			rotateWithRightChild(theParent->right);
		return theParent->right;
	}
}