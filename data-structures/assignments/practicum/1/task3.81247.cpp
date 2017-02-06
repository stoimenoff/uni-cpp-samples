#include <iostream>
#include <stack>

#include "../../../trees/binary/exercises/tree.h"

using std::cout;
using std::endl;
using std::stack;

unsigned int lastDigit(unsigned int number)
{
	return number % 10;
}

unsigned int cutLastDigit(unsigned int number)
{
	return number / 10;
}

bool sumNumbers(BinaryTree<int>& firstTree, BinaryTree<int>& secondTree)
{
	unsigned int carry = 0;
	stack<unsigned short> digits;

	auto firstIt = firstTree.begin();
	auto secondIt = secondTree.begin();

	while(firstIt != firstTree.end() || secondIt != secondTree.end())
	{
		if(firstIt != firstTree.rend())
		{
			carry += *firstIt;
			++firstIt;
		}
		if(secondIt != secondTree.rend())
		{
			carry += *secondIt;
			++secondIt;
		}
		digits.push(lastDigit(carry));
		carry = cutLastDigit(carry);
	}
	while(!digits.empty())
	{
		cout << digits.top();
		digits.pop();
	}
	cout << endl;
	return true;
}

int main()
{
	BinaryTree<int> firstNumber, secondNumber;
	firstNumber.add(5, "").add(2, "L").add(8, "R").add(1, "LL").add(7, "RL");
	secondNumber.add(9, "").add(3, "L").add(4, "R").add(9, "RL");

	sumNumbers(firstNumber, secondNumber);

	return 0;
}
