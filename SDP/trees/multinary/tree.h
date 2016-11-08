#ifndef _MULTINARY_TREE_
#define _MULTINARY_TREE_

#include <list>
#include <queue>
#include <stack>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <map>

using std::list;
using std::queue;
using std::stack;
using std::find;
using std::logic_error;
using std::iterator;
using std::input_iterator_tag;
using std::map;
using std::pair;

template<class T>
class MulatinaryTree;

template<class T>
using TreeIterator = iterator<input_iterator_tag, MulatinaryTree<T> >;

template<class T>
class MulatinaryTree
{
	private:
		T *data = nullptr;
		list<MulatinaryTree<T>> children;
		void copyTree(const MulatinaryTree<T>&);
		void clear();

	public:
		template<class R>
		class BFSIterator : public TreeIterator<R>
		{
			private:
				queue<const MulatinaryTree<R>*> trees;
			public:
				BFSIterator(const MulatinaryTree<R>* root = nullptr)
				{
					if(root != nullptr)
					{
						trees.push(root);
					}
				}
				R operator*() const
				{
					return trees.front()->getData();
				}
				BFSIterator operator++()
				{
					BFSIterator cache = *this;
					for (auto &child : trees.front()->children)
					{
						trees.push(&child);
					}
					trees.pop();
					return cache;
				}
				BFSIterator& operator++(int)
				{
					for (auto &child : trees.front()->children)
					{
						trees.push(&child);
					}
					trees.pop();
					return *this;
				}
				bool hasNext() const
				{
					return !trees.empty();
				}
				bool operator==(const BFSIterator<R>& other) const
				{
					return trees == other.trees;
				}
				bool operator!=(const BFSIterator<R>& other) const
				{
					return !(*this == other);
				}
		};
		template<class R>
		class DFSIterator : public TreeIterator<R>
		{
			private:
				stack<const MulatinaryTree<R>*> trees;
				void popAndAddChildrenToStack()
				{
					const MulatinaryTree<R>* tree = trees.top();
					trees.pop();
					auto iterator = (tree->children).rbegin();
					while(iterator != (tree->children).rend())
					{
						trees.push(&*iterator);
						++iterator;
					}
				}
			public:
				DFSIterator(const MulatinaryTree<R>* root = nullptr)
				{
					if(root != nullptr)
					{
						trees.push(root);
					}
				}
				R operator*() const
				{
					return trees.top()->getData();
				}
				DFSIterator operator++()
				{
					DFSIterator cache = *this;
					popAndAddChildrenToStack();
					return cache;
				}
				DFSIterator& operator++(int)
				{
					popAndAddChildrenToStack();
					return *this;
				}
				bool hasNext() const
				{
					return !trees.empty();
				}
				bool operator==(const DFSIterator<R>& other) const
				{
					return trees == other.trees;
				}
				bool operator!=(const DFSIterator<R>& other) const
				{
					return !(*this == other);
				}
		};

		template<class R>
		class BFSIteration
		{
			public:
				BFSIteration(const MulatinaryTree<R>* tree) : tree(tree) {}
				BFSIterator<R> begin()
				{
					return BFSIterator<R>(tree);
				}
				BFSIterator<R> end()
				{
					return BFSIterator<R>();
				}
			private:
				const MulatinaryTree<R>* tree;
		};

		template<class R>
		class DFSIteration
		{
			public:
				DFSIteration(const MulatinaryTree<R>* tree) : tree(tree) {}
				DFSIterator<R> begin()
				{
					return DFSIterator<R>(tree);
				}
				DFSIterator<R> end()
				{
					return DFSIterator<R>();
				}
			private:
				const MulatinaryTree<R>* tree;
		};
		MulatinaryTree();
		MulatinaryTree(const MulatinaryTree<T>&);
		MulatinaryTree<T>& operator=(const MulatinaryTree<T>&);
		~MulatinaryTree();

		MulatinaryTree<T>& addChild(const MulatinaryTree<T>& tree);
		bool isEmpty() const;
		MulatinaryTree<T>& setData(const T& data);
		T getData() const;

		list<MulatinaryTree<T>> getChildren() const;

		BFSIteration<T> BFS() const;
		DFSIteration<T> DFS() const;
};

template<class T>
void MulatinaryTree<T>::copyTree(const MulatinaryTree<T>& other)
{
	setData(*(other.data));
	children = other.children;
}

template<class T>
void MulatinaryTree<T>::clear()
{
	delete data;
	data = nullptr;
}

template<class T>
MulatinaryTree<T>::MulatinaryTree() {}

template<class T>
MulatinaryTree<T>::MulatinaryTree(const MulatinaryTree<T>& other)
{
	copyTree(other);
}

template<class T>
MulatinaryTree<T>& MulatinaryTree<T>::operator=(const MulatinaryTree<T>& other)
{
	if(this != &other)
	{
		clear();
		copyTree(other);
	}
	return *this;
}

template<class T>
MulatinaryTree<T>::~MulatinaryTree()
{
	clear();
}

template<class T>
MulatinaryTree<T>& MulatinaryTree<T>::addChild(const MulatinaryTree<T>& tree)
{
	if(tree.data == nullptr)
		return *this;
	if(data == nullptr)
		throw logic_error("The tree is empty, cannot add element");
	children.push_back(tree);
	return *this;
}

template<class T>
bool  MulatinaryTree<T>::isEmpty() const
{
	return data == nullptr;
}

template<class T>
MulatinaryTree<T>&  MulatinaryTree<T>::setData(const T& newData)
{
	delete data;
	data = new T(newData);
	return *this;
}

template<class T>
T  MulatinaryTree<T>::getData() const
{
	if(data == nullptr)
		throw logic_error("The tree is empty");
	return *data;
}

template<class T>
list<MulatinaryTree<T>> MulatinaryTree<T>::getChildren() const
{
	return children;
}

template<class T>
MulatinaryTree<T>::BFSIteration<T> MulatinaryTree<T>::BFS() const
{
	return MulatinaryTree<T>::BFSIteration<T>(this);
}

template<class T>
MulatinaryTree<T>::DFSIteration<T> MulatinaryTree<T>::DFS() const
{
	return MulatinaryTree<T>::DFSIteration<T>(this);
}

#endif
