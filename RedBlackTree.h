#pragma once
#include"Except.h"

template<class Comparable>
class RedBlackTree;

template<class Comparable>	//��ǰ��������
class RedBlackNode;       

template<class Comparable>
class RedBlackTree {
public:
	RedBlackTree(const Comparable& negInf);	//������Ĺ��캯��
	~RedBlackTree();	//���������������

	enum{RED,BLACK};

	void insert(const Comparable& x);

	typedef RedBlackNode<Comparable> Node;	//�������ͱ���
//private:  Ϊ�˲��ԣ���ʱ���public
public:   
	Node* header;  //ͷָ��
	Node* nullNode;	//�ս��

	Node* current;	//��ǰ���
	Node* parent;	//�����
	Node* grand;	//�游���
	Node* great;	//���游���

	void rotateWithLeftChild(Node*& k2) const;
	void rotateWithRightChild(Node*& k1) const;

	void doubleRotateWithLeftChild(Node*& k3) const;
	void doubleRotateWithRightChild(Node*& k1) const;
};

template<class Comparable>
class RedBlackNode {
public:	//Ϊ�˲��ԣ���ʱ��Ϊpublic
	Comparable		element;
	RedBlackNode*	left;
	RedBlackNode*	right;
	int				color;

	RedBlackNode(const Comparable& theElement = Comparable(),	//���Ĺ��캯�����ó�ʼ���б���г�ʼ��
		RedBlackNode* lt = NULL,								//theElement��Comparable()Ĭ�ϳ�ʼ��
		RedBlackNode* rt=NULL,
		int c=RedBlackTree<Comparable>::BLACK)
		:element(theElement),left(lt),right(rt),color(c){ }

	friend class RedBlackTree<Comparable>;	//����RedBlackTreeΪ��RedBlackNode����Ԫ��
};

template<class Comparable>
RedBlackTree<Comparable>::RedBlackTree(const Comparable& negInf) {	//������Ĺ��캯��
	nullNode = new Node();
	nullNode->left = nullNode->right = nullNode;
	header = new Node(negInf);
	header->left = header->right = nullNode;
}

template<class Comparable>
RedBlackTree<Comparable>::~RedBlackTree() {	//���������������
	delete nullNode;
	delete header;
}
 
template<class Comparable>
void RedBlackTree<Comparable>::insert(const Comparable& x) {
	current = parent = grand = header;
	nullNode->element = x;		//	��Ա�������Է���private����

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

	//	�Զ�ƽ�� -> �����
}

template<class Comparable>
void RedBlackTree<Comparable>::rotateWithLeftChild(Node*& k2) const {	//����
	Node* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1; 
}

template<class Comparable>
void RedBlackTree<Comparable>::rotateWithRightChild(Node*& k1) const {	//����
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