#ifndef _MULTINARY_TREE_
#define _MULTINARY_TREE_

#include <list>
#include <queue>
#include <stdexcept>

using std::list;
using std::queue;
using std::logic_error;

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
		class BFSIterator
		{
			private:
				queue<const MulatinaryTree<T>*> trees;
			public:
				BFSIterator(const MulatinaryTree<T>* root)
				{
					trees.push(root);
				}
				T operator*() const
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

		};
		MulatinaryTree();
		MulatinaryTree(const MulatinaryTree<T>&);
		MulatinaryTree<T>& operator=(const MulatinaryTree<T>&);
		~MulatinaryTree();

		MulatinaryTree<T>& addChild(const MulatinaryTree<T>& tree);
		bool isEmpty() const;
		MulatinaryTree<T>& setData(const T& data);
		T getData() const;

		BFSIterator<T> BFS() const;
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
MulatinaryTree<T>::BFSIterator<T> MulatinaryTree<T>::BFS() const
{
	return BFSIterator<T>(this);
}

#endif
