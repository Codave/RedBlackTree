#include<iostream>
#include"RedBlackTree.h"

using namespace std;

int main() {

	const int NEG_INF = -99999;
	RedBlackTree<int> t(NEG_INF);
	t.insert(30);
	t.insert(15);
	t.insert(70);
	cout << t.header->right->element << endl;
	cout << t.header->right->left->element << endl;
	cout << t.header->right->right->element << endl;
	cout << "OK" << endl;

	return 0;
}