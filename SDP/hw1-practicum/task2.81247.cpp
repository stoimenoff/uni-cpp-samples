#include <iostream>

#include "bst.h"

using std::cout;
using std::endl;

void reverseOrder(Node<int>*& root)
{
	if(root != nullptr)
	{
		swap(root->left, root->right);
		root->data = - root->data;
		reverseOrder(root->left);
		reverseOrder(root->right);
	}
}

// friend фукнция на BinarySearchTree
void reverseOrder(BinarySearchTree<int>& tree)
{
	reverseOrder(tree.root);
}

int main()
{
	BinarySearchTree<int> tree;
	tree.add(8).add(10).add(4).add(1).add(6).add(11).add(9);

	for(int number : tree)
		cout << number << endl;

	reverseOrder(tree);

	for(int number : tree)
		cout << number << endl;

	return 0;
}
