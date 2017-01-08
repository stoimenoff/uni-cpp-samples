#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <stdexcept>

#include "node.h"

using std::runtime_error;

template <class T>
class BinaryTree
{
	private:
		Node<T> *root;

	public:

		class Inspector
		{
			protected:
				static const unsigned int NO_MOVE = 0;
				static const unsigned int UP = 1;
				static const unsigned int LEFT = 2;
				static const unsigned int RIGHT = 3;

				Node<T> *currentNode;
				Node<T> *previousNode;
				unsigned int lastMove;

				void ensureNotEmpty() const;
			public:
				Inspector(Node<T>*);
				bool isEmpty() const;
				bool hasLeft() const;
				bool hasRight() const;
				bool hasParent() const;
				Inspector& goLeft();
				Inspector& goRight();
				Inspector& goToParent();

				Inspector left() const;
				Inspector right() const;
				Inspector parent() const;

				bool isLeaf() const;
				const T& getData() const;
		};

		class Transformer : public Inspector
		{
			protected:
				Node<T> **treeRootPointer;
			public:
			Transformer(Node<T>**);
			/*Override Inspector functions to return Transformer*/
			Transformer& goLeft();
			Transformer& goRight();
			Transformer& goToParent();

			Transformer left() const;
			Transformer right() const;
			Transformer parent() const;

			/*Modifiers*/
			Transformer& addNewDataNode(const T& data) const;
			Transformer& changeData(const T& data) const;
			BinaryTree<T> abandonLeftSubtree() const;
			BinaryTree<T> abandonRightSubtree() const;
			void adoptAsLeftSubtree(BinaryTree<T>&) const;
			void adoptAsRightSubtree(BinaryTree<T>&) const;
		};

	friend class Transformer;

		BinaryTree();
		BinaryTree(const BinaryTree<T>&);
		BinaryTree<T>& operator = (const BinaryTree<T>&);
		~BinaryTree();
		Inspector getInspector() const;
		Transformer getTransformer();

};

template <class T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
{
	root = copyStructure(other.root);
}

template <class T>
BinaryTree<T>& BinaryTree<T>::operator = (const BinaryTree<T>& other)
{
	if (this != &other)
		root = copyStructure(other.root);
	return *this;
}

template <class T>
BinaryTree<T>::~BinaryTree<T>()
{
	recursiveDeleteStructure(root);
}

template <class T>
typename BinaryTree<T>::Inspector BinaryTree<T>::getInspector() const
{
	return Inspector(root);
}

template <class T>
typename BinaryTree<T>::Transformer BinaryTree<T>::getTransformer()
{
	return Transformer(&root);
}

/*Inspector*/

template <class T>
BinaryTree<T>::Inspector::Inspector(Node<T> *currentNode)
	: currentNode(currentNode), previousNode(nullptr) , lastMove(NO_MOVE) {}

template <class T>
bool BinaryTree<T>::Inspector::isEmpty() const
{
	return currentNode == nullptr;
}

template <class T>
bool BinaryTree<T>::Inspector::hasLeft() const
{
	return !isEmpty() && currentNode->left != nullptr;
}

template <class T>
bool BinaryTree<T>::Inspector::hasRight() const
{
	return !isEmpty() && currentNode->right != nullptr;
}

template <class T>
bool BinaryTree<T>::Inspector::hasParent() const
{
	return !isEmpty() && currentNode->parent != nullptr;
}

template <class T>
void BinaryTree<T>::Inspector::ensureNotEmpty() const
{
	if (isEmpty())
		throw runtime_error("The tree is empty.");
}

template <class T>
typename BinaryTree<T>::Inspector& BinaryTree<T>::Inspector::goLeft()
{
	ensureNotEmpty();
	previousNode = currentNode;
	currentNode = currentNode->left;
	lastMove = LEFT;
	return *this;
}

template <class T>
typename BinaryTree<T>::Inspector& BinaryTree<T>::Inspector::goRight()
{
	ensureNotEmpty();
	previousNode = currentNode;
	currentNode = currentNode->right;
	lastMove = RIGHT;
	return *this;
}

template <class T>
typename BinaryTree<T>::Inspector& BinaryTree<T>::Inspector::goToParent()
{
	if (isEmpty())
	{
		currentNode = previousNode;
		previousNode = nullptr;
	}
	else
	{
		previousNode = currentNode;
		currentNode = currentNode->parent;
	}
	lastMove = UP;
	return *this;
}

template <class T>
typename BinaryTree<T>::Inspector BinaryTree<T>::Inspector::left() const
{
	ensureNotEmpty();
	Inspector inspector(currentNode->left);
	inspector.previousNode = currentNode;
	inspector.lastMove = LEFT;
	return inspector;
}

template <class T>
typename BinaryTree<T>::Inspector BinaryTree<T>::Inspector::right() const
{
	ensureNotEmpty();
	Inspector inspector(currentNode->right);
	inspector.previousNode = currentNode;
	inspector.lastMove = RIGHT;
	return inspector;
}

template <class T>
typename BinaryTree<T>::Inspector BinaryTree<T>::Inspector::parent() const
{
	Node<T> *parent = isEmpty() ? previousNode : currentNode->parent;
	Inspector inspector(parent);
	inspector.lastMove = UP;
	return inspector;
}

template <class T>
bool BinaryTree<T>::Inspector::isLeaf() const
{
	return !hasLeft() && !hasRight();
}

template <class T>
const T& BinaryTree<T>::Inspector::getData() const
{
	ensureNotEmpty();
	return currentNode->data;
}


/*Transformer*/

template <class T>
BinaryTree<T>::Transformer::Transformer(Node<T>** treeRootPointer)
	: Inspector(*treeRootPointer), treeRootPointer(treeRootPointer) {}

template <class T>
typename BinaryTree<T>::Transformer& BinaryTree<T>::Transformer::goLeft()
{
	Inspector::goLeft();
	return *this;
}

template <class T>
typename BinaryTree<T>::Transformer& BinaryTree<T>::Transformer::goRight()
{
	Inspector::goRight();
	return *this;
}

template <class T>
typename BinaryTree<T>::Transformer& BinaryTree<T>::Transformer::goToParent()
{
	Inspector::goToParent();
	return *this;
}

template <class T>
typename BinaryTree<T>::Transformer BinaryTree<T>::Transformer::left() const
{
	Transformer leftTransformer = *this;
	leftTransformer.Inspector::goLeft();
	return leftTransformer;
}

template <class T>
typename BinaryTree<T>::Transformer BinaryTree<T>::Transformer::right() const
{
	Transformer rightTransformer = *this;
	rightTransformer.Inspector::goRight();
	return rightTransformer;
}

template <class T>
typename BinaryTree<T>::Transformer BinaryTree<T>::Transformer::parent() const
{
	Transformer parentTransformer = *this;
	parentTransformer.Inspector::goToParent();
	return parentTransformer;
}

template <class T>
typename BinaryTree<T>::Transformer& BinaryTree<T>::Transformer::addNewDataNode(const T& data) const
{
	if (!Inspector::isEmpty())
		throw runtime_error("Tree is NOT empty.");

	Inspector::currentNode = new Node<T>(data, nullptr, nullptr, Inspector::previousNode);

	//Attach to parent
	if (Inspector::previousNode != nullptr)
	{
		if (Inspector::lastMove == Inspector::LEFT)
			Inspector::previousNode->left = Inspector::currentNode;
		else if (Inspector::lastMove == Inspector::RIGHT)
			Inspector::previousNode->right = Inspector::currentNode;
	}

	if (*treeRootPointer == nullptr)
		*treeRootPointer = Inspector::currentNode;

}

template <class T>
typename BinaryTree<T>::Transformer& BinaryTree<T>::Transformer::changeData(const T& data) const
{
	if (Inspector::isEmpty())
	{
		addNewDataNode(data);
	}
	else
	{
		Inspector::currentNode->data = data;
	}
	return *this;
}

template <class T>
BinaryTree<T> BinaryTree<T>::Transformer::abandonLeftSubtree() const
{
	Inspector::ensureNotEmpty();
	BinaryTree<T> leftSubTree;
	leftSubTree.root = Inspector::currentNode->left;
	detachFromParent(leftSubTree.root);
	return leftSubTree;
}

template <class T>
BinaryTree<T> BinaryTree<T>::Transformer::abandonRightSubtree() const
{
	Inspector::ensureNotEmpty();
	BinaryTree<T> rightSubTree;
	rightSubTree.root = Inspector::currentNode->right;
	detachFromParent(rightSubTree.root);
	return rightSubTree;
}

template <class T>
void BinaryTree<T>::Transformer::adoptAsLeftSubtree(BinaryTree<T>& newLeftSubtree) const
{
	Inspector::ensureNotEmpty();
	if (Inspector::hasLeft())
		recursiveDeleteStructure(Inspector::currentNode->left);
	attachLeftChild(Inspector::currentNode, newLeftSubtree.root);
	newLeftSubtree.root = nullptr;
}

template <class T>
void BinaryTree<T>::Transformer::adoptAsRightSubtree(BinaryTree<T>& newRightSubtree) const
{
	Inspector::ensureNotEmpty();
	if (Inspector::hasRight())
		recursiveDeleteStructure(Inspector::currentNode->right);
	attachRightChild(Inspector::currentNode, newRightSubtree.root);
	newRightSubtree.root = nullptr;
}


#endif
