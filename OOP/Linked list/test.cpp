#include <iostream>

#include "linkedlist.h"

using namespace std;

void testConstOperator (const LinkedList<char> &list)
{
	cout << list[0] << endl;
}

int main ()
{

	LinkedList<char> l;

	l.push_front('!').push_front('i').push_front('h');

	cout << l << endl;

	l[0] = 'b';
	l[2] = '?'; 

	l.push_back('!');
	l.push_back('?');

	cout << l << endl;

	l[2] = 's';

	char c = l[3];

	testConstOperator(l);

	return 0;
}