#ifndef _STACK_H_
#define _STACK_H_

#include<vector>
using std::vector;

template<typename T>
class Stack
{
	public:
		int length() const {return elements.size();}
		bool empty() const {length() == 0;}

		void push(T newElement);
		void pop();
		T top() const;

	private:
		vector<T> elements;
};

template<typename T>
void Stack<T>::push(T newElement)
{
	elements.push_back(newElement);
}

template<typename T>
void Stack<T>::pop()
{
	elements.pop_back();
}

template<typename T>
T Stack<T>::top() const
{
	return elements.back();
}

#endif