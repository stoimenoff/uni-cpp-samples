#ifndef _BST_H_
#define _BST_H_

#include <unordered_set>
#include <stack>
#include <algorithm>

#include "node.h"

using std::unordered_set;
using std::stack;
using std::swap;

template <class T>
class BinarySearchTree
{
private:
	Node<T> *root;
	void copyTree(Node<T>* &targetRoot, const Node<T>* sourceRoot);
	void deleteAll (Node<T> *subTreeRoot);
	void add (Node<T>*& subTreeRoot, const T& data);
	bool member (Node<T>* subTreeRoot, const T&) const;

public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>& other);
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other);

	BinarySearchTree(BinarySearchTree<T>&& other);
	BinarySearchTree<T>& operator=(BinarySearchTree<T>&& other);

	~BinarySearchTree();

	BinarySearchTree<T>& add (const T& data);
	bool member (const T&) const;

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

	friend void reverseOrder(BinarySearchTree<int>&);

};

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr) {}

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other)
{
	copyTree(root, other.root);
}

template <class T>
void BinarySearchTree<T>::copyTree(Node<T>* &targetRoot, const Node<T>* sourceRoot)
{
	if(sourceRoot == nullptr)
	{
		targetRoot = nullptr;
	}
	else
	{
		targetRoot = new Node<T>(sourceRoot->data, nullptr, nullptr);
		copyTree(targetRoot->left, sourceRoot->left);
		copyTree(targetRoot->right, sourceRoot->right);
	}
}

template<class T>
void BinarySearchTree<T>::deleteAll (Node<T> *subTreeRoot)
{
	if (subTreeRoot != nullptr)
	{
		deleteAll (subTreeRoot->left);
		deleteAll (subTreeRoot->right);
		delete subTreeRoot;
	}
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other)
{
	if(this != &other)
	{
		deleteAll(root);
		copyTree(root, other.root);
	}
	return *this;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& other)
{
	root = other.root;
	other.root = nullptr;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& other)
{
	root = other.root;
	other.root = nullptr;
	return *this;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	deleteAll(root);
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::add (const T& data)
{
	add(root, data);
	return *this;
}

template <class T>
void BinarySearchTree<T>::add (Node<T>*& subTreeRoot, const T& data)
{
	if(subTreeRoot == nullptr)
		subTreeRoot = new Node<T>(data);
	else if(data < subTreeRoot->data)
		add(subTreeRoot->left, data);
	else
		add(subTreeRoot->right, data);
}

template <class T>
bool BinarySearchTree<T>::member (const T& data) const
{
	return member(root, data);
}

template <class T>
bool BinarySearchTree<T>::member (Node<T> *subTreeRoot, const T& data) const
{
	if(subTreeRoot == nullptr)
		return false;
	else if (data == subTreeRoot->data)
		return true;
	else if(data < subTreeRoot->data)
		return member(subTreeRoot->left, data);
	else
		return member(subTreeRoot->right, data);
}

template <class T>
bool BinarySearchTree<T>::Iterator::recursivelyTraversed(const Node<T>* root) const
{
	return traversed.find(root) != traversed.end();
}

template <class T>
BinarySearchTree<T>::Iterator::Iterator(const Node<T>* root, bool end, bool reversed)
	: reversed(reversed)
{
	if(root != nullptr && !end)
		nodes.push(root);
}

template <class T>
T BinarySearchTree<T>::Iterator::operator*()
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
typename BinarySearchTree<T>::Iterator& BinarySearchTree<T>::Iterator::operator++()
{
	nodes.pop();
}

template <class T>
bool BinarySearchTree<T>::Iterator::operator==(const Iterator& other) const
{
	return nodes == other.nodes;
}

template <class T>
bool BinarySearchTree<T>::Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::begin() const
{
	return typename BinarySearchTree<T>::Iterator(root);
}

template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::end() const
{
	return typename BinarySearchTree<T>::Iterator(root, true);
}

template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::rbegin() const
{
	return typename BinarySearchTree<T>::Iterator(root, false, true);
}

template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::rend() const
{
	return typename BinarySearchTree<T>::Iterator(root, true, true);
}

#endif // _BST_H_
