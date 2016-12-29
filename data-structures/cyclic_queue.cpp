#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <cstdlib>
#include <stdexcept>
#include <iostream>

template<typename T>
class Queue
{
	public:

		Queue();
		~Queue();

		void push(T newElement);
		T pop();



	private:
		static const unsigned int INITIAL_SIZE = 4;
		T* elements;
		int nextFreeSpace;
		int firstElement;

		int updateNextFreeSpace();
};

template<typename T>
int Queue<T>::updateNextFreeSpace()
{
	nextFreeSpace += 1;
	nextFreeSpace %= INITIAL_SIZE;
	if(elements[nextFreeSpace] != NULL)
	{
		nextFreeSpace = -1;
	}
}

template<typename T>
Queue<T>::Queue()
{
	elements = new T[INITIAL_SIZE] {NULL};
	nextFreeSpace = 0;
	firstElement = 0;
}

template<typename T>
Queue<T>::~Queue()
{
	delete elements;
}

template<typename T>
void Queue<T>::push(T newElement)
{
	if(nextFreeSpace == -1)
	{
		throw std::logic_error("No space");
	}
	elements[nextFreeSpace] = newElement;
	updateNextFreeSpace();
}

template<typename T>
T Queue<T>::pop()
{
	T element = elements[firstElement % INITIAL_SIZE];
	if(element == NULL)
	{
		throw std::logic_error("Queue is empty");
	}
	elements[firstElement % INITIAL_SIZE] = NULL;
	firstElement += 1;

	if(nextFreeSpace == -1)
	{
		nextFreeSpace = firstElement - 1;
	}

	return element;
}

int main()
{
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	std::cout << q.pop() << std::endl;
	q.push(4);
	q.push(5);
	std::cout << q.pop() << std::endl;
	std::cout << q.pop() << std::endl;
	std::cout << q.pop() << std::endl;
	std::cout << q.pop() << std::endl;
}

#endif
