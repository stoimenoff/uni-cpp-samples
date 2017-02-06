#ifndef _TWOSTACKQUEUE_H_
#define _TWOSTACKQUEUE_H_

#include <stack>
#include <cstdlib>

using std::stack;

template<class T>
class TwoStackQueue
{
	private:
		stack<T> inbox, outbox;
		void fillOutboxFromInbox();
	public:
		TwoStackQueue<T>& push(const T&);
		TwoStackQueue<T>& pop();
		T& front();
		size_t size() const;
		bool empty() const;
};

template<class T>
void TwoStackQueue<T>::fillOutboxFromInbox()
{
	if(outbox.empty())
	{
		while(!inbox.empty())
		{
			outbox.push(inbox.top());
			inbox.pop();
		}
	}
}

template<class T>
TwoStackQueue<T>& TwoStackQueue<T>::push(const T& element)
{
	inbox.push(element);
	return *this;
}

template<class T>
TwoStackQueue<T>& TwoStackQueue<T>::pop()
{
	fillOutboxFromInbox();
	outbox.pop();
	return *this;
}

template<class T>
T& TwoStackQueue<T>::front()
{
	fillOutboxFromInbox();
	return outbox.top();
}

template<class T>
size_t TwoStackQueue<T>::size() const
{
	return inbox.size() + outbox.size();
}

template<class T>
bool TwoStackQueue<T>::empty() const
{
	return size() == 0;
}

#endif
