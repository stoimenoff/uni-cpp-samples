#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <assert.h>
#include <cstring>
#include <vector>
#include <stack>
#include <unordered_set>
#include <string>
#include <algorithm>

#include "node.h"

using std::vector;
using std::stack;
using std::unordered_set;
using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::max;

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
	T get (Node<T>* subTreeRoot, const char *trace) const;
	bool member (const T&, Node<T> *subTreeRoot) const;
	void deleteAll (Node<T> *subTreeRoot);
	void copyTree(Node<T>* &targetRoot, const Node<T>* sourceRoot);
	size_t height(Node<T>* subTreeRoot) const;

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

	bool areMirrored(Node<T>* subTreeRoot1, Node<T>* subTreeRoot2) const;
	vector<vector<T>> pathsToLeaves(Node<T>* subTreeRoot) const;

public:
	BinaryTree();
	BinaryTree(const BinaryTree<T>& other);
	BinaryTree<T>& operator=(const BinaryTree<T>& other);

	BinaryTree(BinaryTree<T>&& other);
	BinaryTree<T>& operator=(BinaryTree<T>&& other);

	~BinaryTree();

	BinaryTree<T>& add (const T& data, const char *trace);
	T get (const char *trace) const;
	const BinaryTree<T>& simplePrint () const;
	const BinaryTree<T>& dottyPrint (ostream&) const;
	const BinaryTree<T>& prettyPrint() const;
	bool member (const T&) const;
	size_t height() const;

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
	bool isSymetrical() const;

	vector<vector<T>> pathsToLeaves() const;

	class Iterator
	{
		private:
			stack<const Node<T>*> nodes;
			unordered_set<const Node<T>*> traversed;
			bool reversed;
			bool recursivelyTraversed(const Node<T>*) const;
		public:
			Iterator(const Node<T>* root = nullptr, bool end = false, bool reversed = false);
			T operator*();
			Iterator& operator++();
			bool operator==(const Iterator& other) const;
			bool operator!=(const Iterator& other) const;
	};

	Iterator begin() const;
	Iterator end() const;

	Iterator rbegin() const;
	Iterator rend() const;

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

template <class T>
bool BinaryTree<T>::areMirrored(Node<T>* subTreeRoot1, Node<T>* subTreeRoot2) const
{
	if(subTreeRoot1 == nullptr && subTreeRoot2 == nullptr)
		return true;
	if(subTreeRoot1 == nullptr || subTreeRoot2 == nullptr)
		return false;
	if(subTreeRoot1->data != subTreeRoot2->data)
		return false;
	return areMirrored(subTreeRoot1->left, subTreeRoot2->right) &&
			areMirrored(subTreeRoot1->right, subTreeRoot2->left);
}

template <class T>
bool BinaryTree<T>::isSymetrical() const
{
	if(root == nullptr)
		return true;
	return areMirrored(root->left, root->right);
}

template <class T>
vector<vector<T>> BinaryTree<T>::pathsToLeaves() const
{
	return pathsToLeaves(root);
}

template <class T>
vector<vector<T>> BinaryTree<T>::pathsToLeaves(Node<T>* subTreeRoot) const
{
	vector<vector<T>> paths;
	if(subTreeRoot->left == nullptr && subTreeRoot->right == nullptr)
	{
		vector<T> path = {subTreeRoot->data};
		paths.push_back(path);
		return paths;
	}
	if(subTreeRoot->left != nullptr)
	{
			vector<vector<T>> left = pathsToLeaves(subTreeRoot->left);
			paths.insert(paths.end(), left.begin(), left.end());
	}
	if(subTreeRoot->right != nullptr)
	{
		vector<vector<T>> right = pathsToLeaves(subTreeRoot->right);
		paths.insert(paths.end(), right.begin(), right.end());
	}
	for(auto &path : paths)
	{
		// path.push_back(subTreeRoot->data);
		path.insert(path.begin(), subTreeRoot->data);
	}
	return paths;
}

template <class T>
size_t BinaryTree<T>::height() const
{
	return height(root);
}

template <class T>
size_t BinaryTree<T>::height(Node<T>* subTreeRoot) const
{
	if(subTreeRoot == nullptr)
	{
		return 0;
	}
	return max(height(subTreeRoot->left), height(subTreeRoot->right)) + 1;
}

template <class T>
T BinaryTree<T>::get (Node<T>* subTreeRoot, const char *trace) const
{
	if (subTreeRoot == nullptr)
		assert (false); // no element
	if (strlen(trace) == 0)
		return subTreeRoot->data;
	if (trace[0]=='L')
		return get (subTreeRoot->left, trace + 1);
	if (trace[0]=='R')
		return get (subTreeRoot->right, trace + 1);
	assert(false); // no element
}

template <class T>
T BinaryTree<T>::get (const char *trace) const
{
	return get(root, trace);
}




template <class T>
bool BinaryTree<T>::Iterator::recursivelyTraversed(const Node<T>* root) const
{
	return traversed.find(root) != traversed.end();
}

template <class T>
BinaryTree<T>::Iterator::Iterator(const Node<T>* root, bool end, bool reversed)
	: reversed(reversed)
{
	if(root != nullptr && !end)
		nodes.push(root);
}

template <class T>
T BinaryTree<T>::Iterator::operator*()
{
	const Node<T>* root = nodes.top();
	if(recursivelyTraversed(root))
		return root->data;
	nodes.pop();
	if(reversed)
	{
		if(root->left != nullptr)
			nodes.push(root->left);
		nodes.push(root);
		if(root->right != nullptr)
			nodes.push(root->right);
	}
	else
	{
		if(root->right != nullptr)
			nodes.push(root->right);
		nodes.push(root);
		if(root->left != nullptr)
			nodes.push(root->left);
	}
	traversed.insert(root);
	return **this;
}

template <class T>
typename BinaryTree<T>::Iterator& BinaryTree<T>::Iterator::operator++()
{
	nodes.pop();
}

template <class T>
bool BinaryTree<T>::Iterator::operator==(const Iterator& other) const
{
	return nodes == other.nodes;
}

template <class T>
bool BinaryTree<T>::Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::begin() const
{
	return typename BinaryTree<T>::Iterator(root);
}

template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::end() const
{
	return typename BinaryTree<T>::Iterator(root, true);
}

template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::rbegin() const
{
	return typename BinaryTree<T>::Iterator(root, false, true);
}

template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::rend() const
{
	return typename BinaryTree<T>::Iterator(root, true, true);
}


#endif // _TREE_H_
