#ifndef _TREE_H_
#define _TREE_H_

#include <list>

using std::list;

#include "node.h"

namespace BinarySearchTree
{
	template<class T>
	Node<T> add(const Node<T>& root, const T& newElement)
	{
		Node<T> rootCopy = root;
		if(newElement < root.data)
		{
			if(root.left == nullptr)
			{
				rootCopy.left = new Node<T>(newElement);
				rootCopy.left->parent = rootCopy.left;
			}
			else
			{
				rootCopy.left = new Node<T>(add(*(rootCopy.left), newElement));
				rootCopy.left->parent = rootCopy.left;
			}
		}
		else
		{
			if(root.right == nullptr)
			{
				rootCopy.right = new Node<T>(newElement);
				rootCopy.right->parent = rootCopy.right;
			}
			else
			{
				rootCopy.right = new Node<T>(add(*(rootCopy.right), newElement));
				rootCopy.right->parent = rootCopy.right;
			}
		}
		return rootCopy;
	}

	template<class T>
	T min(const Node<T>& root)
	{
		return (root.left == nullptr) ? root.data : min(*root.left);
	}

	template<class T>
	T max(const Node<T>& root)
	{
		return (root.right == nullptr) ? root.data : max(*root.right);
	}

	template<class T>
	Node<T> remove(const Node<T>& root, const T& element)
	{
		// TODO
	}

	template<class T>
	list<T> sorted(const Node<T>& root)
	{
		list<T> sorted;
		if(root.left != nullptr)
			sorted.splice(sorted.end(), BinarySearchTree::sorted(*root.left));
		sorted.push_back(root.data);
		if(root.right != nullptr)
			sorted.splice(sorted.end(), BinarySearchTree::sorted(*root.right));
		return sorted;
	}
}

#endif
