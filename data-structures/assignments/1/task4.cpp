#include <iostream>
#include "../../trees/binary/binarytree.h"
#include "../../trees/binary/binarytreeutils.h"

using namespace std;

bool readWordFromRoot(const BinaryTree<char>::Inspector treeInspector, const char* word)
{
	if (word[0] =='\0')
		return true;
	if (treeInspector.isEmpty())
		return false;
	if (treeInspector.getData() != word[0])
		return false;
	return readWordFromRoot(treeInspector.left(), word + 1) ||
			readWordFromRoot(treeInspector.right(), word + 1);
}

bool readWord(const BinaryTree<char>::Inspector treeInspector, const char* word)
{
	if (word[0] =='\0')
		return true;
	if (treeInspector.isEmpty())
		return false;

	if (treeInspector.getData() == word[0])
	{
		if (readWordFromRoot(treeInspector.left(), word + 1))
			return true;
		if (readWordFromRoot(treeInspector.right(), word + 1))
			return true;
	}

	return readWord(treeInspector.left(), word) ||
			readWord(treeInspector.right(), word);
}

bool readWord(const BinaryTree<char>& tree, char const* word)
{
	return readWord(tree.getInspector(), word);
}


//Examples

BinaryTree<char> getTreeFrom3(const char* symbols)
{
	BinaryTree<char> tree;
	auto transformer = tree.getTransformer();
	transformer.addData(symbols[1]);
	transformer.left().addData(symbols[0]);
	transformer.right().addData(symbols[2]);
	return tree;
}

int main()
{
	BinaryTree<char> trees[] = {getTreeFrom3("saz"), getTreeFrom3("wor"),
								getTreeFrom3("bsd"), getTreeFrom3("ohg")};
	BinaryTree<char> tree;
	auto transformer = tree.getTransformer();
	transformer.addData('k');
	transformer.adoptAsLeftSubtree(trees[0]);
	transformer.adoptAsRightSubtree(trees[1]);
	transformer.left().right().adoptAsRightSubtree(trees[2]);
	transformer.right().right().adoptAsRightSubtree(trees[3]);

	cout << boolalpha << readWord(tree, "azs") << endl;
	cout << boolalpha << readWord(tree, "ko") << endl;
	cout << boolalpha << readWord(tree, "azsd") << endl;
	cout << boolalpha << readWord(tree, "a") << endl;
	cout << boolalpha << readWord(tree, "w") << endl;
	cout << boolalpha << readWord(tree, "rh") << endl;
	cout << boolalpha << readWord(tree, "kazsb") << endl;

	cout << boolalpha << readWord(tree, "kasb") << endl;
	cout << boolalpha << readWord(tree, "kowo") << endl;

	// dotPrint(cerr, tree);
	return 0;
}
