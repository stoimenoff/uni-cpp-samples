#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <assert.h>
#include <cstring>

#include "node.h"

using std::cout;
using std::endl;
using std::ostream;

template <class ParameterType, class ResultType>
using mapper = ResultType (*)(const ParameterType&);

template <class ParameterType, class ResultType>
using reducer = ResultType (*)(const ResultType&, const ParameterType&);

template <class T>
class BinaryTree
{
private:
	Node<T> *root;
	void simplePrint (Node<T> *subTreeRoot) const;
	void dottyPrint (ostream&, Node<T> *subTreeRoot, int id) const;
	bool add (const T& data, const char *trace, Node<T>*&);
	bool member (const T&, Node<T> *subTreeRoot) const;
	void deleteAll (Node<T> *subTreeRoot);
	void copyTree(Node<T>* &targetRoot, const Node<T>* sourceRoot);
	
	template <class R>
	Node<R>* map(mapper<T, R> mapping, Node<T> *subTreeRoot) const;

	template <class R>
	void reduce(reducer<T, R> reducing, Node<T> *subTreeRoot, R& currentResult) const;

	template<typename U>
  	friend class BinaryTree;

public:
	BinaryTree();
	BinaryTree(const BinaryTree<T>& other);
	BinaryTree<T>& operator=(const BinaryTree<T>& other);

	BinaryTree(BinaryTree<T>&& other);
	BinaryTree<T>& operator=(BinaryTree<T>&& other);

	~BinaryTree();

	BinaryTree<T>& add (const T& data, const char *trace);
	void simplePrint () const;
	void dottyPrint (ostream&) const;
	bool member (const T&) const;
	
	template <class R>
	BinaryTree<R> map(mapper<T, R> mapping) const;

	template <class R>
	R reduce(reducer<T, R> reducing, R initial) const;

};

template<class T>
bool BinaryTree<T>::member (const T& x) const
{
	return member (x,root);
}


template<class T>
bool BinaryTree<T>::member (const T& x, Node<T> *subTreeRoot) const
{
	if (subTreeRoot == NULL)
		return false;

	return subTreeRoot->data == x ||
	       member (x,subTreeRoot->left) ||
	       member (x,subTreeRoot->right);
}


template<class T>
void BinaryTree<T>::deleteAll (Node<T> *subTreeRoot)
{
	if (subTreeRoot == NULL)
		return;
	deleteAll (subTreeRoot->left);
	deleteAll (subTreeRoot->right);
	delete subTreeRoot;
}

template <class T>
BinaryTree<T>& BinaryTree<T>::add(const T& x, const char *trace)
{
   add(x, trace, root);
   return *this;
}

template <class T>
bool BinaryTree<T>::add(const T& x, const char *trace, Node<T>* &subTreeRoot)
{
	if (subTreeRoot == NULL)
	{
		assert (strlen(trace) == 0);
		subTreeRoot = new Node<T> (x,NULL,NULL);
		return true;
	}

	assert (strlen(trace) > 0);

	if (trace[0]=='L')
		return add (x,trace+1,subTreeRoot->left);

	assert (trace[0]=='R');
	return add (x,trace+1,subTreeRoot->right);
}

template <class T>
BinaryTree<T>::BinaryTree() : root(NULL) {}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
{
	copyTree(root, other.root);
}

template <class T>
void BinaryTree<T>::copyTree(Node<T>* &targetRoot, const Node<T>* sourceRoot)
{
	if(sourceRoot == NULL)
	{
		targetRoot = NULL;
		return;
	}
	targetRoot->data = sourceRoot->data;
	copyTree(targetRoot->left, sourceRoot->left);
	copyTree(targetRoot->right, sourceRoot->right);
}

template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other)
{
	if(this != &other)
	{
		deleteAll(root);
		copyTree(root, other.root);
	}
	return *this;
}

template <class T>
BinaryTree<T>::BinaryTree(BinaryTree<T>&& other)
{
	root = other.root;
	other.root = NULL;
}

template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T>&& other)
{
	root = other.root;
	other.root = NULL;
	return *this;
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
	deleteAll(root);
}

template <class T>
void BinaryTree<T>::simplePrint() const
{
	simplePrint(root);
	cout << endl;
}

template <class T>
void BinaryTree<T>::simplePrint(Node<T> *subTreeRoot) const
{
	if (subTreeRoot == NULL)
		return;
	cout << subTreeRoot->data << " ";
	simplePrint (subTreeRoot->left);
	simplePrint (subTreeRoot->right);
}

template <class T>
void BinaryTree<T>::dottyPrint(ostream& out) const
{
	out << "digraph G{" << endl;
	dottyPrint(out, root, 0);
	out << "}" << endl;
}

template <class T>
void BinaryTree<T>::dottyPrint(ostream& out, Node<T> *subTreeRoot, int id) const
{
	if(subTreeRoot == NULL)
		return;
	out << id << "[label=\"" << subTreeRoot->data << "\"];" << endl;
	
	if(id > 0)
		out << (id - 1) / 2 << " -> " << id << ";" << endl;
	
	dottyPrint(out, subTreeRoot->left, 2*id + 1);
	dottyPrint(out, subTreeRoot->right, 2*id + 2);
}

template <class T>
template <class R>
BinaryTree<R> BinaryTree<T>::map(mapper<T, R> mapping) const
{
	BinaryTree<R> newTree;
	newTree.root = map(mapping, root);
	return newTree;
}

template <class T>
template <class R>
Node<R>* BinaryTree<T>::map(mapper<T, R> mapping, Node<T> *subTreeRoot) const
{
	if(subTreeRoot == NULL)
		return NULL;
	return new Node<R>(mapping(subTreeRoot->data),
					   map(mapping, subTreeRoot->left),
					   map(mapping, subTreeRoot->right));
}

template <class T>
template <class R>
void BinaryTree<T>::reduce(reducer<T, R> reducing, Node<T>*subTreeRoot, R& currentResult) const
{
	currentResult = reducing(currentResult, subTreeRoot->data);
	if(subTreeRoot->left != NULL)
		reduce(reducing, subTreeRoot->left, currentResult);
	if(subTreeRoot->right != NULL)
		reduce(reducing, subTreeRoot->right, currentResult);
}

template <class T>
template <class R>
R BinaryTree<T>::reduce(reducer<T, R> reducing, R initial) const
{
	R result = initial;
	reduce(reducing, root, result);
	return result;
}

#endif // _TREE_H_
