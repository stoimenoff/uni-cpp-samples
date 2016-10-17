#include "person.h"

void Person::init(const char *name, int id)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->id = id;
}

Person::Person(const char* name, int id)
{
	init(name, id);
}

Person::Person(const Person &other)
{
	init(other.name, other.id);
}

Person& Person::operator = (const Person &other)
{
	if (this != &other)
	{
		delete[] name;
		init(other.name, other.id);		
	}
	return *this;
}

Person::~Person()
{
	delete[] name;
}

void Person::print() const
{
	std::cout << "Az sam person:\n";
	std::cout << name << std::endl;
	std::cout << id << std::endl;
}