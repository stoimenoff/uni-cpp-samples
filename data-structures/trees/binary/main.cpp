#include "binarytree.h"

#include <iostream>

using namespace std;

template <class T>
void dotPrint(ostream& out, typename BinaryTree<T>::Inspector treeInspector, size_t id)
{
	out << id << "[label=\"" << treeInspector.getData() << "\"];" << endl;
	if (treeInspector.hasLeft())
	{
		out << id << " -> " << id + 1 << ";" << endl;
		treeInspector.goLeft();
		dotPrint<T>(out, treeInspector, id + 1);
		treeInspector.goToParent();
	}
	if (treeInspector.hasRight())
	{
		out << id << " -> " << id + 2 << ";" << endl;
		treeInspector.goRight();
		dotPrint<T>(out, treeInspector, id + 2);
		treeInspector.goToParent();
	}
}

template <class T>
void dotPrint(ostream& out, const BinaryTree<T>& tree)
{
	out << "digraph G\n{\n";
	dotPrint<T>(out, tree.getInspector(), 0);
	out << "}\n";
}

int main()
{
	BinaryTree<int> tree;

	BinaryTree<int>::Transformer tr = tree.getTransformer();

	tr.addNewDataNode(5);

	tr.goLeft();
	tr.addNewDataNode(2);

	tr.goToParent();
	tr.goRight();
	tr.addNewDataNode(3);

	dotPrint(cout, tree);

	return 0;
}
