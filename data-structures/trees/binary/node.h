#ifndef _NODE_H_
#define _NODE_H_

template <class T>
struct Node
{
	T data;
	Node<T> *left;
	Node<T> *right;
	Node<T> *parent;

	Node(const T& data, Node<T> *left = nullptr, Node<T> *right = nullptr, Node<T> *parent = nullptr)
		: data(data), left(left), right(right), parent(parent) {}
};

template <class T>
void attachLeftChild(Node<T>* parent, Node<T>* child)
{
	parent->left = child;
	if (child != nullptr)
		child->parent = parent;
}

template <class T>
void attachRightChild(Node<T>* parent, Node<T>* child)
{
	parent->right = child;
	if (child != nullptr)
		child->parent = parent;
}

template <class T>
void detachFromParent(Node<T>* child)
{
	if (child->parent != nullptr)
	{
		if (child->parent->left == child)
			child->parent->left = nullptr;
		if (child->parent->right == child)
			child->parent->right = nullptr;
	}
	child->parent = nullptr;
}

template <class T>
void recursiveDeleteStructure (Node<T> *root)
{
	if (root != nullptr)
	{
		recursiveDeleteStructure(root->left);
		recursiveDeleteStructure(root->right);
		delete root;
	}
}

template <class T>
Node<T>* copyStructure(Node<T> *root)
{
	if (root == nullptr)
		return root;
	Node<T> *rootCopy = new Node<T>(root->data, copyStructure(root->left), copyStructure(root->right));
	if (rootCopy->left != nullptr)
		rootCopy->left->parent = rootCopy;
	if (rootCopy->right != nullptr)
		rootCopy->right->parent = rootCopy;
	return rootCopy;
}

#endif // _NODE_H_
