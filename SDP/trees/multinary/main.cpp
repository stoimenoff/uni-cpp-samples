#include "tree.h"
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::boolalpha;

MulatinaryTree<int> getIntTree(int data, vector<int> childrenData)
{
	MulatinaryTree<int> tree;
	tree.setData(data);
	for(auto childData : childrenData)
		tree.addChild(MulatinaryTree<int>().setData(childData));
	return tree;
}

int maxNumberOfChildren(MulatinaryTree<int> tree)
{
	queue<MulatinaryTree<int> > trees;
	trees.push(tree);
	int max = 0, numberOfChildren;
	while(!trees.empty())
	{
		numberOfChildren = tree.getChildren().size();
		if(numberOfChildren > max)
		{
			max = numberOfChildren;
		}
		for (auto child : trees.front().getChildren())
		{
			trees.push(child);
		}
		trees.pop();
	}
	return max;
}

int depth(MulatinaryTree<int> tree)
{
	if(tree.getChildren().empty())
	{
		return 0;
	}
	int maxChildDepth = 0, currentChildDepth = 0;
	for (auto child : tree.getChildren())
	{
		currentChildDepth = depth(child);
		if(currentChildDepth > maxChildDepth)
		{
			maxChildDepth = currentChildDepth;
		}
	}
	return maxChildDepth + 1;
}

int maxElement(MulatinaryTree<int> tree)
{

	int max = 0;
	for (auto element : tree.BFS())
		if(element > max)
			max = element;
	return max;
}

bool isElement(MulatinaryTree<int> tree, int n)
{
	for (auto element : tree.BFS())
		if(element == n)
			return true;
	return false;
}

int main()
{
	MulatinaryTree<int> tree;
	tree.setData(-1);

	for (int i = 0; i < 10; i+=4)
	{
		tree.addChild(getIntTree(i, {i + 1, i + 2, i + 3}));
	}

	cout << "---------BFS---------" << endl;
	for (auto element : tree.BFS())
	{
		cout << element << endl;
	}
	cout << "---------------------" << endl;
	cout << "---------DFS---------" << endl;
	for (auto element : tree.DFS())
	{
		cout << element << endl;
	}
	cout << "---------------------" << endl;

	cout << maxNumberOfChildren(tree) << endl;
	cout << maxElement(tree) << endl;
	cout << boolalpha;
	cout << isElement(tree, -1) << endl;
	cout << isElement(tree, 2) << endl;
	cout << isElement(tree, 11) << endl;
	cout << isElement(tree, -2) << endl;
	cout << isElement(tree, 12) << endl;

	cout << depth(tree) << endl;

	return 0;
}
