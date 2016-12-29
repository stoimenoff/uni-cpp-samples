#ifndef _NODE_H_
#define _NODE_H_

template<class T>
struct Node
{
	T data;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;

	Node(T data, Node<T>* parent = nullptr, Node<T>* left = nullptr,
		Node<T>* right = nullptr):
		data(data), left(left), right(right), parent(parent) {}

	Node(const Node<T>& other)
	{
		data = other.data;
		left = (other.left == nullptr) ? nullptr : new Node<T>(*other.left);
		right = (other.right == nullptr) ? nullptr : new Node<T>(*other.right);
		parent = nullptr;
	}

	Node<T>& operator=(const Node<T>& other)
	{
		if(this != &other)
		{
			delete left;
			delete right;
			data = other.data;
			left = (other.left == nullptr) ? nullptr : new Node<T>(*other.left);
			right = (other.right == nullptr) ? nullptr : new Node<T>(*other.right);
			parent = nullptr;
		}
		return *this;
	}

	~Node()
	{
		delete left;
		delete right;
	}

};

#endif
