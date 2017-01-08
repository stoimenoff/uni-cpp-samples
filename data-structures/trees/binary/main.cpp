#include "binarytree.h"
#include "binarytreeutils.h"

using namespace std;

int main()
{
	BinaryTree<int> tree;

	BinaryTree<int>::Transformer tr = tree.getTransformer();

	tr.addData(5);

	tr.goLeft();
	tr.addData(2);

	tr.goToParent();
	tr.goRight();
	tr.addData(3);

	dotPrint(cout, tree);

	return 0;
}
