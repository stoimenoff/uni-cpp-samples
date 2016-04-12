#include "student.h"

/*Helper private methods*/
void Student::init(const char* name, double avgGrades, unsigned int fcNumber)
{
	setName(name);
    averageGrades = avgGrades;
    facultyNumber = fcNumber;
}
/*Constructors and assignment operator*/
Student::Student(const char* name, double avgGrades, unsigned int fcNumber)
{
	init(name, avgGrades, fcNumber);
}

Student::Student(const Student& other)
{
	init(other.name, other.averageGrades, other.facultyNumber);
}

Student& Student::operator = (const Student& other)
{
	if (this != &other)
	{
		delete[] name;
		init(other.name, other.averageGrades, other.facultyNumber);		
	}
	return *this;
}
Student::~Student()
{
	delete[] name;
}
/*Setters*/
void Student::setName(const char* name)
{
	this->name = new char [strlen(name) + 1];
    strcpy(this->name, name);
}

void Student::setAverageGrades(double averageGrades)
{
	this->averageGrades = averageGrades;
}

void Student::setFacultyNumber(unsigned int facultyNumber)
{
	this->facultyNumber = facultyNumber;	
}
/*Print function*/
void Student::print() const
{
	std::cout << "---------Student---------\n";
	std::cout << "Name: " << name << std::endl;
	std::cout << "Average grades: " << averageGrades << std::endl;
	std::cout << "Faculty number: " << facultyNumber << std::endl;
}
/*Ostream operator*/
std::ostream& operator << (std::ostream& out, const Student& student)
{
	out << "---------Student---------\n";
	out << "Name: " << student.getName() << std::endl;
	out << "Average grades: " << student.getAverageGrades() << std::endl;
	out << "Faculty number: " << student.getFacultyNumber() << std::endl;
	return out;
}