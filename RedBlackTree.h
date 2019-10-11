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
};

template<class Comparable>
class RedBlackNode {
public:	//Ϊ�˲��ԣ���ʱ��Ϊ����
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