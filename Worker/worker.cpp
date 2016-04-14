#include "worker.h"

void Worker::init(const char *name, unsigned int hourPayment)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->hourPayment = hourPayment;
}

Worker::Worker(const char *name, unsigned int hourPayment)
{
	init(name, hourPayment);
}

Worker::Worker(const Worker &other)
{
	init(other.name, other.hourPayment);
}

Worker& Worker::operator = (const Worker &other)
{
	if (this != &other)
	{
		delete[] name;
		init(other.name, other.hourPayment);
	}
	return *this;
}

Worker::~Worker()
{
	delete[] name;
}

unsigned int Worker::getHourPayment() const
{
	return hourPayment;
}

const char* Worker::getName() const
{
	return name;
}

void Worker::print() const
{
	std::cout << "-----------------------------" << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Hour payment: " << hourPayment << std::endl;
}