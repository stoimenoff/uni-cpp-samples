#include "../../trees/binary/binarytree.h"
#include "../../trees/binary/binarytreeutils.h"
#include "print.h"

#include <list>
#include <algorithm>

using std::list;
using std::any_of;

typedef unsigned short digit;


list<list<digit>> concatenateLevels(list<list<digit>> left, list<list<digit>> right)
{
	if (left.size() < right.size())
		left.resize(right.size());
	auto leftIterator = left.begin();
	auto rightIterator = right.begin();
	for (; rightIterator != right.end(); ++leftIterator, ++rightIterator)
	{
		list<digit>& leftLevel = *leftIterator;
		list<digit>& rightLevel = *rightIterator;
		leftLevel.splice(leftLevel.end(), rightLevel);
	}
	return left;
}

list<list<digit>> levels(typename BinaryTree<digit>::Inspector treeInspector)
{
	if (treeInspector.isEmpty())
		return {};

	list<list<digit>> lvls = concatenateLevels(levels(treeInspector.left()),
												levels(treeInspector.right()));
	lvls.push_front({treeInspector.getData()});
	return lvls;
}

list<list<digit>> levels(const BinaryTree<digit>& tree)
{
	return levels(tree.getInspector());
}

bool containsRootLeafPath(typename BinaryTree<digit>::Inspector treeInspector,
						list<digit> path)
{
	if (treeInspector.isEmpty() && path.empty())
		return true;
	if (treeInspector.isEmpty())
		return false;
	if (path.empty())
		return false;
	if (path.front() != treeInspector.getData())
		return false;
	path.pop_front();
	return containsRootLeafPath(treeInspector.left(), path) ||
			containsRootLeafPath(treeInspector.right(), path);
}

bool containsRootLeafPath(const BinaryTree<digit>& tree, const list<digit>& path)
{
	return containsRootLeafPath(tree.getInspector(), path);
}

bool checkLevelSameAsRootLeafPath(const BinaryTree<digit>& tree)
{
	auto isRootLeafPathInTree = [tree] (const list<digit>& path)
	{
		return containsRootLeafPath(tree, path);
	};
	list<list<digit>> lvls = levels(tree);
	return any_of(lvls.begin(), lvls.end(), isRootLeafPathInTree);
}

//Examples

BinaryTree<digit> getTreeFrom3(digit root, digit left, digit right)
{
	BinaryTree<digit> tree;
	auto transformer = tree.getTransformer();
	transformer.addData(root);
	transformer.left().addData(left);
	transformer.right().addData(right);
	return tree;
}

int main()
{
	/*
				9
		2 				2
	1	  3			4		6
			9 			 (3)	4
		  9   2	 			  6   3
	*/
	BinaryTree<digit> trees[] = {getTreeFrom3(2, 1, 3), getTreeFrom3(2, 4, 6),
								getTreeFrom3(9, 9, 2), getTreeFrom3(4, 6, 3)};
	BinaryTree<digit> tree;
	auto transformer = tree.getTransformer();
	transformer.addData(9);
	transformer.adoptAsLeftSubtree(trees[0]);
	transformer.adoptAsRightSubtree(trees[1]);
	transformer.left().right().adoptAsRightSubtree(trees[2]);
	transformer.right().right().adoptAsRightSubtree(trees[3]);

	// dotPrint(std::cerr, tree);


	for(const auto& level : levels(tree))
		std::cout << level << std::endl;
	std::cout << std::boolalpha << checkLevelSameAsRootLeafPath(tree) << std::endl;

	transformer.right().right().left().addData(3);

	// dotPrint(std::cerr, tree);

	for(const auto& level : levels(tree))
		std::cout << level << std::endl;
	std::cout << std::boolalpha << checkLevelSameAsRootLeafPath(tree) << std::endl;

	return 0;
}
