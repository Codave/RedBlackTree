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

	void rotateWithLeftChild(Node*& k2) const;	//����
	void rotateWithRightChild(Node*& k1) const;	//����

	void doubleRotateWithLeftChild(Node*& k3) const;	//����
	void doubleRotateWithRightChild(Node*& k1) const;	//����

	void handleReorient(const Comparable& item);
	RedBlackNode<Comparable>* rotate(const Comparable& item, Node* parent) const;  //��ʵ����ֵ��Node*

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
	nullNode = new Node();	//�ս�㣨NULL��
	nullNode->left = nullNode->right = nullNode;
	header = new Node(negInf);    //αͷ���
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

		if (current->left->color == RED && current->right->color == RED) {
			handleReorient(x);
		}
	}

	if (current != nullNode) {    //�ҵ�����ȵĽ��
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
void RedBlackTree<Comparable>::doubleRotateWithLeftChild(Node*& k3) const {//������������
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

template<class Comparable>
void RedBlackTree<Comparable>::doubleRotateWithRightChild(Node*& k1) const {//������������
	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}

template<class Comparable>
inline void RedBlackTree<Comparable>::handleReorient(const Comparable& item) {
	//��ɫ
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

	//����ת

	//˫��ת
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