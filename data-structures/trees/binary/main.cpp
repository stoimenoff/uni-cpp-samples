#include "binarytree.h"

#include <iostream>

using namespace std;

template <class T>
void dotPrint(ostream& out, typename BinaryTree<T>::Inspector treeInspector, size_t id)
{
	if (treeInspector.isEmpty())
	{
		out << id << "[label=\"NULL\" shape=point];" << endl;
		return;
	}
	out << id << "[label=\"" << treeInspector.getData() << "\"];" << endl;

	out << id << " -> " << 2*id + 1 << ";" << endl;
	dotPrint<T>(out, treeInspector.left(), 2*id + 1);

	out << id << " -> " << 2*id + 2 << ";" << endl;
	dotPrint<T>(out, treeInspector.right(), 2*id + 2);
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

	tr.addData(5);

	tr.goLeft();
	tr.addData(2);

	tr.goToParent();
	tr.goRight();
	tr.addData(3);

	dotPrint(cout, tree);

	return 0;
}
