#ifndef _NODE_H_
#define _NODE_H_

#define NULL 0

template <typename T>
class Node
{

	public:
		Node(const T& data = NULL, Node<T>* next = NULL)
			: data(data), next(next) {};
		T data;
		Node<T>* next;
};

#endif
