#include "employee.h"

void Employee::init(const char *position, int salary)
{
	this->position = new char[strlen(position) + 1];
	strcpy(this->position, position);
	this->salary = salary;
}


Employee::Employee(const char *name, int id, const char* position, int salary)
	: Person(name, id)
{
	init(position, salary);
}

Employee::Employee(const Employee &other) : Person(other)
{
	init(other.position, other.salary);
}

Employee& Employee::operator = (const Employee &other)
{
	if (this != &other)
	{
		Person::operator = (other);
		delete[] position;
		init(other.position, other.salary);
	}
	return *this;
}

Employee::~Employee()
{
	delete[] position;
}

void Employee::print() const
{
	Person::print();
	printMe();
}

void Employee::printMe() const
{
	std::cout << "Az sam employee\n";
	std::cout << salary << std::endl;
	std::cout << position << std::endl;
}