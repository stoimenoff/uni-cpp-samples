#include "intern.h"

Intern::Intern(const char *name, int id, const char* position, 
			int salary, int fn, int grade, int period)
	: Person(name, id), Student(name, id, fn, grade), 
	  Employee(name, id, position, salary), period(period) {}


void Intern::print() const
{
	Person::print();
	Student::printMe();
	Employee::printMe();
	std::cout << "Az sam intern\n";
	std::cout << period << std::endl;	
}