#include "list.h"

int main()
{
	DoubleLList<int> ints;

	for (int i = 0; i < 10; ++i)
	{
		ints.toEnd(i);
	}

	ints.print();

	return 0;
}
