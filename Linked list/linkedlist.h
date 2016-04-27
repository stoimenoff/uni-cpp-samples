#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <cassert>
#include "node.h"

template <typename T>
class LinkedList
{
	private:
		Node<T> *first;
		Node<T> *last;
		int length;
		void copyNodes(const LinkedList<T> &other);
		void deleteNodes();
		T removeOnlyElement();
		Node<T>* get(int index) const;
	public:
		int size() const {return length;}

		LinkedList<T>& push_front(const T &newElement);
		LinkedList<T>& push_back(const T &newElement);

		LinkedList();
		LinkedList(const LinkedList<T> &other);
		LinkedList<T>& operator = (const LinkedList<T> &other);
		~LinkedList();

		T pop_front();
		T pop_back();

		T pop(int index);
		void push(int index, const T &newElement);

		T& operator [] (int index);
		T operator [] (int index) const;

		template <typename U>
		friend std::ostream& operator << (std::ostream& out, const LinkedList<U> &list);

};

template <typename T>
LinkedList<T>& LinkedList<T>::push_front(const T &newElement)
{
	length += 1;
	if (first == NULL)
	{
		first = new Node<T>(newElement, NULL, NULL);
		return *this;
	}
	if (last == NULL)
	{
		last = first;
		first = new Node<T>(newElement, last, NULL);	
		last->previous = first;
		return *this;
	}
	first = new Node<T>(newElement, first, NULL);
	first->next->previous = first;
	return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::push_back(const T &newElement)
{
	length += 1;
	if (first == NULL)
	{
		return push_front(newElement);
	}
	if (last == NULL)
	{
		last = new Node<T>(newElement, NULL, first);
		first->next = last;
		return *this;
	}
	last = new Node<T>(newElement, NULL, last);
	last->previous->next = last;
	return *this;	
}


template <typename T>
void LinkedList<T>::copyNodes(const LinkedList<T> &other)
{
	first = NULL;
	last = NULL;
	Node<T> *current = other.first;
	while (current != NULL)
	{
		push_back(current->data);
		current = current->next;
	}
}

template <typename T>
void LinkedList<T>::deleteNodes()
{
	if (first == NULL)
		return;
	Node<T> *current = first->next; //second element
	while (current != NULL)
	{
		delete current->previous;
		current = current->next;
	}
	delete last;
}

template <typename T>
LinkedList<T>::LinkedList() : first(NULL), last(NULL) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
{
	copyNodes(other);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator = (const LinkedList<T> &other)
{
	if (this != &other)
	{
		deleteNodes();
		copyNodes(other);
	}
	return *this;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	deleteNodes();
}

template <typename T>
T LinkedList<T>::removeOnlyElement()
{
	T result;
	result = first->data;
	first = NULL;
	last = NULL;
	length -= 1;
	return result;
}

template <typename T>
T LinkedList<T>::pop_front()
{
	assert(length > 0);
	if (length == 1)
		return removeOnlyElement();
	T result = first->data;
	first = first->next;
	delete first->previous;
	first->previous = NULL;
	length -= 1;
	return result;
}

template <typename T>
T LinkedList<T>::pop_back()
{
	assert(length > 0);
	if (length == 1)
		return removeOnlyElement();
	T result = last->data;
	last = last->previous;
	delete last->next;
	last->next = NULL;
	length -= 1;
	return result;
}

template <typename T>
Node<T>* LinkedList<T>::get(int index) const
{
	Node<T> *current = first;
	for (int i = 0; i < index; ++i)
	{
		current = current->next;
	}
	return current;
}

template <typename T>
T LinkedList<T>::pop(int index)
{
	assert(length > 0 && index >= 0 && index < length);
	if (index == 0)
		return pop_front();
	if (index == length - 1)
		return pop_back();
	Node<T> *toBePopped = get(index);
	toBePopped->previous->next = toBePopped->next;
	toBePopped->next->previous = toBePopped->previous;
	T result = toBePopped->data;
	delete toBePopped;
	length -= 1;
	return result;
}

template <typename T>
void LinkedList<T>::push(int index, const T &newElement)
{
	assert(index >= 0);
	assert(index < length || (index == 0 && length == 0));
	if (index == 0)
		return push_front(newElement);
	if (index == length - 1)
		return push_back(newElement);
	Node<T> *toBeMoved = get(index);
	Node<T> *newNode = new Node<T>(newElement, toBeMoved, toBeMoved->previous);
	toBeMoved->previous = &newNode;
	toBeMoved->previous->next = &newNode;
	length += 1;
}

template <typename T>
T& LinkedList<T>::operator [] (int index)
{
	assert(length > 0 && index >= 0 && index < length);
	return get(index)->data;
}

template <typename T>
T LinkedList<T>::operator [] (int index) const
{
	assert(length > 0 && index >= 0 && index < length);
	return get(index)->data;
}

template <typename U>
std::ostream& operator << (std::ostream& out, const LinkedList<U> &list)
{
	Node<U> *current = list.first;
	while (current != NULL)
	{
		out << current->data << " ";
		current = current->next;
	}
	return out;
}

#endif
