#include "student.h"

Student::Student(const char* name, int id, int fn, int grade)
	: Person(name, id), fn(fn), grade(grade) {}

void Student::print() const
{
	Person::print();
	printMe();
}

void Student::printMe() const
{
	std::cout << "Az sam studen\n";
	std::cout << fn << std::endl;
	std::cout << grade << std::endl;	
}