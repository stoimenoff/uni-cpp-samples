#ifndef _NODE_H_
#define _NODE_H_

#define NULL 0

template <typename T>
class Node
{

	public:
		Node(const T& data = NULL, Node<T>* next = NULL);
		Node(const Node<T>& other);
		Node<T>& operator = (const Node<T>& other);

		T data;
		Node<T>* next;
	private:
		void init(const T& data, Node<T>* next);
};

template <typename T>
void Node<T>::init(const T& data, Node<T>* next)
{
	this->data = data;
	this->next = next;
}

template <typename T>
Node<T>::Node(const T& data, Node<T>* next)
{
	init(data, next);
}

template <typename T>
Node<T>::Node(const Node<T>& other)
{
	init(other.data, other.next);
}

template <typename T>
Node<T>& Node<T>::operator = (const Node<T>& other)
{
	init(other.data, other.next);
}

#endif