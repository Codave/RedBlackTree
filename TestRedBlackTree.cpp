#include<iostream>
#include"RedBlackTree.h"

using namespace std;

int main() {

	const int NEG_INF = -99999;
	RedBlackTree<int> t(NEG_INF);
	t.insert(12);
	t.insert(16);
	t.insert(8);
	t.insert(10);
	t.insert(4);
	t.insert(14);
	t.insert(2);
	t.insert(6);
	t.insert(5);

	cout << t.header->right->left->left->right->left->element << endl;
	cout << t.header->right->left->element << endl;
	t.doubleRotateWithLeftChild(t.header->right->left);
	cout << t.header->right->left->element << endl;
	cout << t.header->right->left->left->right->element << endl;

	return 0;
}