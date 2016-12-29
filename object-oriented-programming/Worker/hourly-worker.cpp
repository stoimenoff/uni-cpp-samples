#include "hourly-worker.h"

void HourlyWorker::setHoursWorked(const int hoursWorked)
{
	if (hoursWorked < 0 || hoursWorked > 168)
	{
		//error
	}
	this->hoursWorked = hoursWorked;
}

void HourlyWorker::init(int hoursWorked, const char* workType)
{
	setHoursWorked(hoursWorked);
	this->workType = new char[strlen(name) + 1];
	strcpy(this->workType, workType);
}

void HourlyWorker::setWorkType(const char* workType)
{
	delete[] this->workType;
	this->workType = new char[strlen(name) + 1];
	strcpy(this->workType, workType);
}

HourlyWorker::HourlyWorker(const char *name, unsigned int hourPayment, 
			int hoursWorked, const char* workType) : Worker(name, hourPayment)
{
	init(hoursWorked, workType);
}

HourlyWorker::HourlyWorker(const HourlyWorker &other) : Worker(other)
{
	init(other.hoursWorked, other.workType);
}

HourlyWorker& HourlyWorker::operator = (const HourlyWorker &other)
{
	if (this != & other)
	{
		Worker::operator=(other);
		delete[] workType;
		init(other.hoursWorked, other.workType);
	}
	return *this;
}

HourlyWorker::~HourlyWorker()
{
	delete[] workType;
}

int HourlyWorker::getHoursWorked() const
{
	return hoursWorked;
}

const char * HourlyWorker::getWorkType() const
{
	return workType;
}

void HourlyWorker::print() const
{
	Worker::print();
	std::cout << "Hours worked: " << hoursWorked << std::endl;
	std::cout << "Work type: " << workType << std::endl;
}