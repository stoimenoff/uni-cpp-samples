#include <iostream>
#include "../../trees/binary/binarytree.h"
#include "../../trees/binary/binarytreeutils.h"

using namespace std;

int sumNodes(const BinaryTree<int>::Inspector treeInspector)
{
	int sum = 0;
	if (treeInspector.isEmpty())
		return sum;
	sum += sumNodes(treeInspector.left());
	sum += sumNodes(treeInspector.right());

	bool shouldSumCurrent = true;
	if (treeInspector.hasParent())
		if (treeInspector.parent().getData() <= treeInspector.getData())
			shouldSumCurrent = false;
	if (treeInspector.hasRight())
		if (treeInspector.right().getData() >= treeInspector.getData())
			shouldSumCurrent = false;
	if (treeInspector.hasLeft())
		if (treeInspector.left().getData() >= treeInspector.getData())
			shouldSumCurrent = false;

	return shouldSumCurrent ? sum + treeInspector.getData() : sum;
}

int sumNodes(const BinaryTree<int>& tree)
{
	return sumNodes(tree.getInspector());
}


//Example

BinaryTree<int> getTreeFrom3(int left, int root, int right)
{
	BinaryTree<int> tree;
	auto transformer = tree.getTransformer();
	transformer.addData(root);
	transformer.left().addData(left);
	transformer.right().addData(right);
	return tree;
}

int main()
{
	BinaryTree<int> trees[] = {getTreeFrom3(1, 2, 3), getTreeFrom3(4, 5, 6),
								getTreeFrom3(7, 8, 9), getTreeFrom3(10, 11, 12)};
	BinaryTree<int> tree;
	auto transformer = tree.getTransformer();
	transformer.addData(19);
	transformer.adoptAsLeftSubtree(trees[0]);
	transformer.adoptAsRightSubtree(trees[1]);
	transformer.left().right().adoptAsRightSubtree(trees[2]);
	transformer.right().left().adoptAsRightSubtree(trees[3]);

	cout << sumNodes(tree) << endl;

	// dotPrint(cerr, tree);
	return 0;
}
