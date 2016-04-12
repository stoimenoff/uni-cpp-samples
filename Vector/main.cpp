#include "vector.h"

int main()
{
	Vector<int> v1;

	v1.pushBack(1);
	v1.pushBack(2);
	v1.pushBack(3);
	v1.pushBack(4);

	std::cout << v1 << std::endl;

	v1.pushBack(5);
	v1.pushBack(6);
	v1.pushBack(7);
	v1.pushBack(8);
	v1.pushBack(9);
	v1.pushBack(10);
	v1.pushBack(11);

	std::cout << v1 << std::endl;

	v1.popBack();
	v1.popBack();

	std::cout << v1 << std::endl;

	v1.pushBack(10);
	v1.pushBack(11);	

	std::cout << v1 << std::endl;

	std::cout << "Size: " << v1.Size() << std::endl;

	v1.insertAt(0, 22);
	std::cout << v1 << std::endl;

	v1.removeAt(0);
	std::cout << v1 << std::endl;

	v1.insertAt(5, 22);
	std::cout << v1 << std::endl;

	v1.removeAt(5);
	std::cout << v1 << std::endl << std::endl;

	v1.insertAt(0, 0);
	std::cout << v1 << std::endl << std::endl;

	std::cout << v1[0] << std::endl;
	std::cout << v1[5] << std::endl;
	std::cout << v1[8] << std::endl;
	std::cout << v1[10] << std::endl;

	v1[11] = 22;

	std::cout << v1[11] << std::endl;
	std::cout << v1 << std::endl;

	return 0;
}