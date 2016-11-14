#include <iostream>

using std::cout;
using std::endl;

#include "binarysearchtree.h"

int main()
{
	Node<int> root(2);
	root = BinarySearchTree::add(root, 4);
	root = BinarySearchTree::add(root, 5);
	root = BinarySearchTree::add(root, 7);
	root = BinarySearchTree::add(root, 3);
	root = BinarySearchTree::add(root, 6);
	root = BinarySearchTree::add(root, 10);

	for(auto element : BinarySearchTree::sorted(root))
		cout << element << " ";
	cout << endl;

	cout << BinarySearchTree::min(root) << endl;
	cout << BinarySearchTree::max(root) << endl;
}
