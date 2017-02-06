#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <cassert>

using std::cout;

#include "node.h"

template <class T>
using predicate = bool(*)(const T&);

template <class T>
using mapper = T(*)(const T&);

template <class T>
class DoubleLList
{
	public:
		DoubleLList();
		DoubleLList(const DoubleLList& other);
		DoubleLList<T>& operator=(const DoubleLList& other);
		~DoubleLList();

		bool empty() const;
		void print() const;
		int length() const;
		bool member(const T& element) const;
		DoubleLList<T> filter(predicate<T> elementFilter) const;

		void toEnd(const T& element);
		void pop();
		void insertAfter(int index, const T& element);
		void insertBefore(int index, const T& element);
		void insertElem(int index, const T& element);
		void deleteAfter(int index, T& deletedElement);
		void deleteBefore(int index, T& deletedElement);
		void deleteElem(int index, T& deletedElement);
		void map(mapper<T> mutator);
		void concat(const DoubleLList<T> &other);

	private:
		Node<T> *start;
		Node<T> *end;
		int size;

		void toFront(const T& element);
		void popFront();
		void copy(const DoubleLList<T>& other);
		void clear();


};

template<class T>
void DoubleLList<T>::toEnd(const T& element)
{
	size += 1;
	if(start == nullptr)
	{
		start = new Node<T>(element, nullptr, nullptr);
		end = start;
	}
	else
	{
		end->next = new Node<T>(element, nullptr, end);
		end = end->next;
	}
}

template<class T>
void DoubleLList<T>::toFront(const T& element)
{
	size += 1;
	if(start == nullptr)
	{
		start = new Node<T>(element, nullptr, nullptr);
		end = start;
	}
	else
	{
		start->previous = new Node<T>(element, start, nullptr);
		start = start->previous;
	}
}

template<class T>
void DoubleLList<T>::pop()
{
	if(start == end)
	{
		size = 0;
		delete start;
		start = end = nullptr;
	}
	else
	{
		size -= 1;
		end = end->previous;
		delete end->next;
		end->next = nullptr;
	}
}

template<class T>
void DoubleLList<T>::popFront()
{
	if(start == end)
	{
		size = 0;
		delete start;
		start = end = nullptr;
	}
	else
	{
		size -= 1;
		start = start->next;
		delete start->previous;
		start->previous = nullptr;
	}
}

template<class T>
void DoubleLList<T>::copy(const DoubleLList<T>& other)
{
	size = 0;
	start = end = nullptr;
	Node<T>* node = other.start;
	while(node != nullptr)
	{
		toEnd(node->data);
		node = node->next;
	}
}

template<class T>
void DoubleLList<T>::clear()
{
	while(!empty())
	{
		pop();
	}
}

template<class T>
DoubleLList<T>::DoubleLList() : start(nullptr), end(nullptr), size(0) {}

template<class T>
DoubleLList<T>::DoubleLList(const DoubleLList& other)
{
	copy(other);
}

template<class T>
DoubleLList<T>& DoubleLList<T>::operator=(const DoubleLList& other)
{
	if(this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

template<class T>
DoubleLList<T>::~DoubleLList()
{
	clear();
}

template<class T>
int DoubleLList<T>::length() const
{
	return size;
}

template<class T>
bool DoubleLList<T>::empty() const
{
	return length() == 0;
}

template<class T>
void DoubleLList<T>::print() const
{
	Node<T>* node = start;
	while(node != nullptr)
	{
		cout << node->data << " ";
		node = node->next;
	}
}

template<class T>
bool DoubleLList<T>::member(const T& element) const
{
	Node<T>* node = start;
	while(node != nullptr)
	{
		if(node->data == element)
		{
			return true;
		}
		node = node->next;
	}
	return false;
}

template<class T>
DoubleLList<T> DoubleLList<T>::filter(predicate<T> elementFilter) const
{
	DoubleLList<T> filtred;
	Node<T>* node = start;
	while(node != nullptr)
	{
		if(elementFilter(node->data))
		{
			filtred.toEnd(node->data);
		}
		node = node->next;
	}
	return filtred;
}

template<class T>
void DoubleLList<T>::insertElem(int index, const T& element)
{
	assert(index >= 0 && index < size);
	if(index == 0)
	{
		toFront(element);
	}
	else if(index == size - 1)
	{
		toEnd(element);
	}
	else
	{
		size += 1;
		Node<T>* node = start;
		for (int i = 0; i < index; ++i)
		{
			node = node->next;
		}
		Node<T>* newNode = new Node<T>(element, node, node->previous);
		node->previous->next = newNode;
		node->previous = newNode;

	}
}

template<class T>
void DoubleLList<T>::insertAfter(int index, const T& element)
{
	assert(index >= 0 && index < size);
	if(index == size - 1)
	{
		toEnd(element);
	}
	else
	{
		insertElem(index + 1, element);
	}
}

template<class T>
void DoubleLList<T>::insertBefore(int index, const T& element)
{
	assert(index >= 0 && index < size);
	if(index == 0)
	{
		toFront(element);
	}
	else
	{
		insertElem(index - 1, element);
	}
}

template<class T>
void DoubleLList<T>::deleteElem(int index, T& deletedElement)
{
	assert(index >= 0 && index < size);
	if(index == 0)
	{
		deletedElement = start->data;
		popFront();
	}
	else if(index == size - 1)
	{
		deletedElement = end->data;
		pop();
	}
	else
	{
		size -= 1;
		Node<T>* node = start;
		for (int i = 0; i < index; ++i)
		{
			node = node->next;
		}
		deletedElement = node->data;
		node->previous->next = node->next;
		node->next->previous = node->previous;
		delete node;
	}
}

template<class T>
void DoubleLList<T>::deleteAfter(int index, T& deletedElement)
{
	assert(index >= 0 && index < size - 1);
	if(index == size - 2)
	{
		deletedElement = end->data;
		pop();
	}
	else
	{
		deleteElem(index + 1, deletedElement);
	}
}

template<class T>
void DoubleLList<T>::deleteBefore(int index, T& deletedElement)
{
	assert(index >= 1 && index < size);
	if(index == 1)
	{
		deletedElement = start->data;
		popFront();
	}
	else
	{
		deleteElem(index - 1, deletedElement);
	}
}


template<class T>
void DoubleLList<T>::map(mapper<T> mutator)
{
	Node<T>* node = start;
	while(node != nullptr)
	{
		node->data = mutator(node->data);
		node = node->next;
	}
}

template<class T>
void DoubleLList<T>::concat(const DoubleLList<T> &other)
{
	Node<T>* node = other.start;
	while(node != nullptr)
	{
		toEnd(node->data);
		node = node->next;
	}
}

#endif
