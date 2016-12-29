#ifndef _UNIVERSITY_H_
#define _UNIVERSITY_H_

#include "student.h"
#include <cassert>
#include <algorithm>

class University
{
	public:
		/*Constructors and assignment operator*/
		University(unsigned int capacity = 16);
		University(const University& other);
		University& operator = (const University& other);
		~University();
		/*Interface functions*/
		bool addStudent(const Student& student);
		bool removeStudent(unsigned int facultyNumber);
		Student& getStudent(unsigned int facultyNumber);
		void print() const;
		void sortStudents();
	private:
		Student* students;
		int studentsNumber;
		int arrayCapacity;
		void resize(int newCapacity);
		void copyStudents(const University& other);
		int findStudent(int facultyNumber) const;

	/*Ostream operator*/
	friend std::ostream& operator << (std::ostream& out, const University& university);
};

#endif