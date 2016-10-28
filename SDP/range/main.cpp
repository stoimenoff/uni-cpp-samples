#include <iostream>
#include "range.h"

using std::cout;
using std::endl;

int main()
{
	for(int i : range(10))
		cout << i << " ";
	cout << endl;

	for(int i : range(2, 10))
		cout << i << " ";
	cout << endl;

	for(int i : range(1, 10, 2))
		cout << i << " ";
	cout << endl;

	for(int i : range(3, 10, 3))
		cout << i << " ";
	cout << endl;

	for(int i : range(0, 10, 2))
		cout << i << " ";
	cout << endl;

	for(int i : range(10, 0, -2))
		cout << i << " ";
	cout << endl;

	for(int i : range(10, -1, -1))
		cout << i << " ";
	cout << endl;

	for(int i : range(10, -1, -3))
		cout << i << " ";
	cout << endl;

	return 0;
}
