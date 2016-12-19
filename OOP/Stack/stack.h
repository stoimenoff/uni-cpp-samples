#ifndef _STACK_H_
#define _STACK_H_

#define NULL 0

#include "node.h"
#include <iostream>

template <typename T>
class Stack
{

	public:
		Stack();
		Stack(const Stack<T>& other);
		Stack<T>& operator = (const Stack<T>& other);
		~Stack();

		int length() const {return size;};
		bool isEmpty() const {return size == 0;};

		void push(T element);
		T pop();
		T getTop() const;
		void reverse();

	template <typename M>
	friend std::ostream& operator << (std::ostream& out, const Stack<M>& stack);

	private:

		Node<T>* top;
		int size;
		void deleteElements();
		void copyElements(const Stack<T>& other);

};

template <typename T>
void Stack<T>::deleteElements()
{
	Node<T>* curr = top;
	while(top != NULL)
	{
		top = top->next;
		delete curr;
		curr = top;
	}
}

template <typename T>
void Stack<T>::copyElements(const Stack<T>& other)
{
	size = other.size;
	top = NULL;
	Node<T>* curr = other.top;
	while(curr)
	{
		push(curr->data);
		curr = curr->next;
	}
	reverse();
}

template <typename T>
Stack<T>::Stack()
{
	top = NULL;
	size = 0;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other)
{
	copyElements(other);
}
template <typename T>
Stack<T>& Stack<T>::operator = (const Stack<T>& other)
{
	if (this != &other)
	{
		deleteElements();
		copyElements(other);
	}
	return *this;
}

template <typename T>
Stack<T>::~Stack()
{
	deleteElements();
}

template <typename T>
void Stack<T>::push(T element)
{
	Node<T>* oldTop = top;
	top = new Node<T>(element);
	top->next = oldTop;
	size += 1;
}

template <typename T>
T Stack<T>::pop()
{
	T result = top->data;
	Node<T>* newTop = top->next;
	delete top;
	top = newTop;
	size -= 1;
	return result;
}

template <typename T>
T Stack<T>::getTop() const
{
	return top->data;
}

template <typename T>
void Stack<T>::reverse()
{
	if(size > 1)
	{
		Node<T>* current = new Node<T>(top->data);
		Node<T>* next = top->next;
		while(next)
		{
			current = new Node<T>(next->data, current);
			next = next->next;
		}
		deleteElements();
		top = current;
	}
}


/*Ostream operator*/
template <typename T>
std::ostream& operator << (std::ostream& out, const Stack<T>& stack)
{
	Node<T>* current = stack.top;
	while(current)
	{
		out << current->data << " ";
		current = current->next;
	}
	out << std::endl;
	return out;
}

#endif
