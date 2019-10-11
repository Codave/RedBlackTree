#include<iostream>
#include"RedBlackTree.h"

using namespace std;

int main() {

	const int NEG_INF = -99999;
	RedBlackTree<int> t(NEG_INF);
	t.insert(30);
	t.insert(15);
	t.insert(70);
	t.insert(20);

	cout << t.header->right->element << endl;
	cout << t.header->right->left->element << endl;
	cout << t.header->right->right->element << endl;
	cout << t.header->right->left->right->element << endl;

	cout << "向右转" << endl;
	t.rotateWithLeftChild(t.header->right);
	cout << t.header->right->element << endl;
	cout << t.header->right->right->left->element << endl;

	cout << "向左转" << endl;
	t.rotateWithRightChild(t.header->right);
	cout << t.header->right->element << endl;
	cout << t.header->right->left->element << endl;
	cout << t.header->right->right->element << endl;
	cout << t.header->right->left->right->element << endl;

	cout << "OK" << endl;

	return 0;
}