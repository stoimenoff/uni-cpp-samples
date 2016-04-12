#include "polynom.h"

int main()
{
	double coef1[6] = {1, 2, 3, 4, 5, 6};
	double coef2[3] = {10, 15, 20};

	Polynom f(4);

	Polynom g(5, coef1);

	Polynom h(2, coef2);

	std::cout << "f = " << f << std::endl;
	std::cout << "g = " << g << std::endl;
	std::cout << "h = " << h << std::endl;

	std::cout << "f + g = " << f + g << std::endl;
	std::cout << "g + h = " << g + h << std::endl;

	std::cout << "-h = " << -h << std::endl;
	std::cout << "g - h = " << g - h << std::endl;

	std::cout << "g * h = " << g * h << std::endl;

	std::cout << "g(0) = " << g(0) << std::endl;
	std::cout << "g(1) = " << g(1) << std::endl;
	std::cout << "g(2) = " << g(2) << std::endl;
	
	std::cout << "h(3) = " << h(3) << std::endl;

	return 0;
}