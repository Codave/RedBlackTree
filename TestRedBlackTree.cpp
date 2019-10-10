#include<iostream>
#include"RedBlackTree.h"

using namespace std;

int main() {

	const int NEG_INF = -99999;
	RedBlackTree<int> t(NEG_INF);
	t.insert(30);
	cout << "OK" << endl;

	return 0;
}