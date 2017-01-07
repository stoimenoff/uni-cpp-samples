#ifndef _NODE_H_
#define _NODE_H_

template <class T>
struct Node
{
	T data;
	Node<T> *left;
	Node<T> *right;

	Node(const T& data, Node<T> *left = nullptr, Node<T> *right = nullptr)
		: data(data), left(left), right(right) {}
};

#endif // _NODE_H_
