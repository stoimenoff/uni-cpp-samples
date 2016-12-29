#include "university.h"
#include <iostream>

int main()
{
	Student pesho("Pesho", 2.5, 1);
	Student gosho("Gosho", 3.5, 2);
	Student stamat("Stamat", 3, 3);
	Student penka("Penka", 4.2, 4);
	Student dinko("Dinko", 2.2, 5);

	Student dublicat("Dinko2", 2.1, 5);

	University SU;

	SU.addStudent(pesho);
	SU.addStudent(gosho);
	SU.addStudent(stamat);
	SU.addStudent(penka);
	SU.addStudent(dinko);
	SU.addStudent(dublicat);

	std::cout << SU << std::endl;

	SU.removeStudent(3);
	std::cout << "Removed Stamat." << std::endl;
	std::cout << SU << std::endl;

	SU.sortStudents();
	std::cout << "Sorted by grade." << std::endl;
	std::cout << SU << std::endl;

	std::cout << "Get Pesho." << std::endl;
	std::cout << SU.getStudent(1) << std::endl;

	std::cout << "Set Pesho's name to Pesho2." << std::endl;
	SU.getStudent(1).setName("Pesho2");
	std::cout << SU.getStudent(1) << std::endl;

	return 0;
}