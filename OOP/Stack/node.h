#ifndef _NODE_H_
#define _NODE_H_

template <typename T>
class Node
{

	public:
		Node(const T& data, Node<T>* next = NULL)
			: data(data), next(next) {};
		T data;
		Node<T>* next;
};

#endif
