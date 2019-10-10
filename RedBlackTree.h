#pragma once

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

	typedef RedBlackNode<Comparable> Node;	//�������ͱ���
private:
	Node* header;  //ͷָ��
	Node* nullNode;	//�ս��
};

template<class Comparable>
class RedBlackNode {

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