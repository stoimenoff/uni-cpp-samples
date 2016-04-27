#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include <iostream>
#include <cstring>
#include "person.h"

class Employee : virtual public Person
{
	protected:
		char *position;
		int salary;
		void init(const char *position, int salary);

	public:
		Employee(const char *name = "", int id = 0, const char* position = "", int salary = 0);
		Employee(const Employee &other);
		Employee& operator = (const Person &other);
		~Employee();

		void print() const;
};

#endif
