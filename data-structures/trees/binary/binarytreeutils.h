#ifndef _BINARY_TREE_UTILITIES_
#define _BINARY_TREE_UTILITIES_

#include <iostream>

#include "binarytree.h"

using std::ostream;
using std::endl;

template <class T>
void dotPrint(ostream& out, typename BinaryTree<T>::Inspector treeInspector, size_t id)
{
	if (treeInspector.isEmpty())
	{
		out << id << "[label=\"NULL\" shape=point style=invis];" << endl;
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
	out << "graph [ordering=\"out\"];\n";
	dotPrint<T>(out, tree.getInspector(), 0);
	out << "}\n";
}

#endif
