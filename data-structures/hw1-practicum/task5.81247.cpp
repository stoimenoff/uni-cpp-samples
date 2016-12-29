#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::queue;

bool odd(int number)
{
	return number % 2 == 1;
}

int main()
{
	int firstElement, index, generated = 0;
	cin >> firstElement >> index;

	queue<int> sequence;
	sequence.push(firstElement);
	generated = 1;

	while(generated < index)
	{
		if(odd(generated))
		{
			sequence.push(sequence.front() + 1);
		}
		else
		{
			sequence.push(sequence.front() * 2);
			sequence.pop();
		}
		generated += 1;
	}

	cout << sequence.back() << endl;

	return 0;
}
