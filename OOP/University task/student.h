#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <cstring>
#include <iostream>

class Student
{
	public:
		/*Constructors and assignment operator*/
		Student(const char* name = "", double avgGrades = 0, unsigned int fcNumber = 0);
		Student(const Student& other);
		Student& operator = (const Student& other);
		~Student();
		/*Setters*/
		void setName(const char* name);
		void setAverageGrades(double averageGrades);
		void setFacultyNumber(unsigned int facultyNumber);
		/*Getters*/
		const char * getName() const {return name;};
		double getAverageGrades() const {return averageGrades;};
		unsigned int getFacultyNumber() const {return facultyNumber;};
		/*Print function*/
		void print() const;
	private:
		char* name;
		double averageGrades;
		unsigned int facultyNumber;
		void init(const char* name, double avgGrades, unsigned int fcNumber);
};

/*Ostream operator*/
std::ostream& operator << (std::ostream& out, const Student& student);

#endif
