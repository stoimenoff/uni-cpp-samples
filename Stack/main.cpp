#include "stack.h"
#include <iostream>

int main()
{
	Stack<int> st;

	st.push(2);
	st.push(5);
	st.push(4);
	st.push(3);
	st.push(2);
	st.push(1);

	std::cout << st << std::endl;

	st.reverse();

	std::cout << st << std::endl;

	Stack<int> st2 = st;

	while(!st.isEmpty())
	{
		std::cout << st.pop() << std::endl;
	}

	std::cout << st2 << std::endl;

	return 0;
}