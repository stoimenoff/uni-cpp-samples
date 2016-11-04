#include "tree.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

MulatinaryTree<int> getIntTree(int data, vector<int> childrenData)
{
	MulatinaryTree<int> tree;
	tree.setData(data);
	for(auto childData : childrenData)
		tree.addChild(MulatinaryTree<int>().setData(childData));
	return tree;
}

int main()
{
	MulatinaryTree<int> tree;
	tree.setData(-1);

	for (int i = 0; i < 10; i+=4)
	{
		tree.addChild(getIntTree(i, {i + 1, i + 2, i + 3}));
	}

	for (auto element : tree.BFS())
	{
		cout << element << endl;
	}

	for (auto element : tree.DFS())
	{
		cout << element << endl;
	}

	return 0;
}
