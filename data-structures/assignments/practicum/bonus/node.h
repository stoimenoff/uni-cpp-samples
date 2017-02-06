#ifndef _NODE_H_
#define _NODE_H_

template <typename T>
class Node
{
	public:
		Node(const T &data, Node<T> *next, Node<T> *previous)
			: data(data), next(next), previous(previous) {}
		T data;
		Node<T> *next;
		Node<T> *previous;
};

#endif
