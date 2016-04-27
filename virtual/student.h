#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>
#include "person.h"

class Student : virtual public Person
{
	protected:
		int fn;
		int grade;

	public:
		Student(const char* name = "", int id = 0, int fn = 0, int grade = 0);

		void print() const;
		void printMe() const;
		
};

#endif
