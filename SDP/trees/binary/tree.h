#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <assert.h>
#include <cstring>
#include <vector>
#include <string>

#include "node.h"

using std::vector;
using std::string;
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
	void prettyPrint(Node<T> *subTreeRoot, int level) const;
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

	vector<T> listLeaves(Node<T>* subTreeRoot) const;
	string findTrace(const T& element, Node<T>* subTreeRoot) const;
	vector<T> level(int k, Node<T>* subTreeRoot) const;
	vector<T*> depthTraverseInducedList(Node<T>* subTreeRoot) const;
	vector<T*> leftRootRightInducedList(Node<T>* subTreeRoot) const;

public:
	BinaryTree();
	BinaryTree(const BinaryTree<T>& other);
	BinaryTree<T>& operator=(const BinaryTree<T>& other);

	BinaryTree(BinaryTree<T>&& other);
	BinaryTree<T>& operator=(BinaryTree<T>&& other);

	~BinaryTree();

	BinaryTree<T>& add (const T& data, const char *trace);
	const BinaryTree<T>& simplePrint () const;
	const BinaryTree<T>& dottyPrint (ostream&) const;
	const BinaryTree<T>& prettyPrint() const;
	bool member (const T&) const;

	template <class R>
	BinaryTree<R> map(mapper<T, R> mapping) const;

	template <class R>
	R reduce(reducer<T, R> reducing, R initial) const;

	vector<T> listLeaves() const;
	string findTrace(const T& element) const;
	vector<T> level(int k) const;

	T& operator[](int i);
	T operator[](int i) const;

	bool isBST() const;

};

template<class T>
bool BinaryTree<T>::member (const T& x) const
{
	return member (x,root);
}


template<class T>
bool BinaryTree<T>::member (const T& x, Node<T> *subTreeRoot) const
{
	if (subTreeRoot == nullptr)
		return false;

	return subTreeRoot->data == x ||
			member (x,subTreeRoot->left) ||
			member (x,subTreeRoot->right);
}


template<class T>
void BinaryTree<T>::deleteAll (Node<T> *subTreeRoot)
{
	if (subTreeRoot == nullptr)
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
	if (subTreeRoot == nullptr)
	{
		assert (strlen(trace) == 0);
		subTreeRoot = new Node<T> (x,nullptr,nullptr);
		return true;
	}

	assert (strlen(trace) > 0);

	if (trace[0]=='L')
		return add (x,trace+1,subTreeRoot->left);

	assert (trace[0]=='R');
	return add (x,trace+1,subTreeRoot->right);
}

template <class T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
{
	copyTree(root, other.root);
}

template <class T>
void BinaryTree<T>::copyTree(Node<T>* &targetRoot, const Node<T>* sourceRoot)
{
	if(sourceRoot == nullptr)
	{
		targetRoot = nullptr;
		return;
	}
	targetRoot = new Node<T>(sourceRoot->data, nullptr, nullptr);
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
	other.root = nullptr;
}

template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T>&& other)
{
	root = other.root;
	other.root = nullptr;
	return *this;
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
	deleteAll(root);
}

template <class T>
const BinaryTree<T>& BinaryTree<T>::simplePrint() const
{
	simplePrint(root);
	cout << endl;
	return *this;
}

template <class T>
void BinaryTree<T>::simplePrint(Node<T> *subTreeRoot) const
{
	if (subTreeRoot == nullptr)
		return;
	cout << subTreeRoot->data << " ";
	simplePrint (subTreeRoot->left);
	simplePrint (subTreeRoot->right);
}

template <class T>
void BinaryTree<T>::prettyPrint(Node<T> *subTreeRoot, int level) const
{
	if(subTreeRoot == nullptr)
	{
		return;
	}
	prettyPrint(subTreeRoot->right, level + 1);
	cout << string().append(4 * level, ' ') << subTreeRoot->data << endl;
	prettyPrint(subTreeRoot->left, level + 1);
}

template <class T>
const BinaryTree<T>& BinaryTree<T>::prettyPrint() const
{
	prettyPrint(root, 0);
	return *this;
}

template <class T>
const BinaryTree<T>& BinaryTree<T>::dottyPrint(ostream& out) const
{
	out << "digraph G{" << endl;
	dottyPrint(out, root, 0);
	out << "}" << endl;
	return *this;
}

template <class T>
void BinaryTree<T>::dottyPrint(ostream& out, Node<T> *subTreeRoot, int id) const
{
	if(subTreeRoot == nullptr)
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
	if(subTreeRoot == nullptr)
		return nullptr;
	return new Node<R>(mapping(subTreeRoot->data),
					   map(mapping, subTreeRoot->left),
					   map(mapping, subTreeRoot->right));
}

template <class T>
template <class R>
void BinaryTree<T>::reduce(reducer<T, R> reducing, Node<T>*subTreeRoot, R& currentResult) const
{
	currentResult = reducing(currentResult, subTreeRoot->data);
	if(subTreeRoot->left != nullptr)
		reduce(reducing, subTreeRoot->left, currentResult);
	if(subTreeRoot->right != nullptr)
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

template <class T>
vector<T> BinaryTree<T>::listLeaves(Node<T>* subTreeRoot) const
{
	vector<T> leaves;
	if(subTreeRoot == nullptr)
	{
		return leaves;
	}
	if(subTreeRoot->left == nullptr && subTreeRoot->right == nullptr)
	{
		leaves.push_back(subTreeRoot->data);
	}
	vector<T> leftLeaves = listLeaves(subTreeRoot->left);
	vector<T> rightLeaves = listLeaves(subTreeRoot->right);
	leaves.insert(leaves.end(), leftLeaves.begin(), leftLeaves.end());
	leaves.insert(leaves.end(), rightLeaves.begin(), rightLeaves.end());
	return leaves;
}

template <class T>
string BinaryTree<T>::findTrace(const T& element, Node<T>* subTreeRoot) const
{
	if(subTreeRoot == nullptr)
	{
		return "-";
	}
	if(subTreeRoot->data == element)
	{
		return "";
	}
	string leftTraceOfElement = findTrace(element, subTreeRoot->left);
	if(leftTraceOfElement != "-")
	{
		return leftTraceOfElement.insert(0, 1, 'L');
	}
	string rightTraceOfElement = findTrace(element, subTreeRoot->right);
	if(rightTraceOfElement != "-")
	{
		return rightTraceOfElement.insert(0, 1, 'R');
	}
	return "-";
}

template <class T>
vector<T> BinaryTree<T>::listLeaves() const
{
	return listLeaves(root);
}

template <class T>
string BinaryTree<T>::findTrace(const T& element) const
{
	return findTrace(element, root);
}

template <class T>
vector<T> BinaryTree<T>::level(int k, Node<T>* subTreeRoot) const
{
	vector<T> elements;
	if(subTreeRoot == nullptr)
	{
		return elements;
	}
	if(k == 0)
	{
		elements.push_back(subTreeRoot->data);
		return elements;
	}
	vector<T> elementsFromLeft = level(k - 1, subTreeRoot->left);
	vector<T> elementsFromRight = level(k - 1, subTreeRoot->right);
	elements.insert(elements.end(), elementsFromLeft.begin(), elementsFromLeft.end());
	elements.insert(elements.end(), elementsFromRight.begin(), elementsFromRight.end());
	return elements;
}

template <class T>
vector<T> BinaryTree<T>::level(int k) const
{
	assert(k >= 0);
	return level(k, root);
}

template <class T>
vector<T*> BinaryTree<T>::depthTraverseInducedList(Node<T>* subTreeRoot) const
{
	vector<T*> elements;
	if(subTreeRoot == nullptr)
	{
		return elements;
	}
	elements.push_back(&subTreeRoot->data);
	vector<T*> elementsFromLeft = depthTraverseInducedList(subTreeRoot->left);
	vector<T*> elementsFromRight = depthTraverseInducedList(subTreeRoot->right);
	elements.insert(elements.end(), elementsFromLeft.begin(), elementsFromLeft.end());
	elements.insert(elements.end(), elementsFromRight.begin(), elementsFromRight.end());
	return elements;
}

template <class T>
vector<T*> BinaryTree<T>::leftRootRightInducedList(Node<T>* subTreeRoot) const
{
	vector<T*> elements;
	if(subTreeRoot == nullptr)
	{
		return elements;
	}
	vector<T*> elementsFromLeft = leftRootRightInducedList(subTreeRoot->left);
	vector<T*> elementsFromRight = leftRootRightInducedList(subTreeRoot->right);
	elements.insert(elements.end(), elementsFromLeft.begin(), elementsFromLeft.end());
	elements.push_back(&subTreeRoot->data);
	elements.insert(elements.end(), elementsFromRight.begin(), elementsFromRight.end());
	return elements;
}

template <class T>
T& BinaryTree<T>::operator[](int i)
{
	return *depthTraverseInducedList(root).at(i);
}

template <class T>
T BinaryTree<T>::operator[](int i) const
{
	return *depthTraverseInducedList(root).at(i);
}

template <class T>
bool BinaryTree<T>::isBST() const
{
	vector<T*> elements = leftRootRightInducedList(root);
	for (int i = 0; i < elements.size() - 1; ++i)
	{
		if(*elements[i] >= *elements[i + 1])
		{
			return false;
		}
	}
	return true;
}

#endif // _TREE_H_
