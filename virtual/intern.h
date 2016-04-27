#ifndef _INTERN_H_
#define _INTERN_H_

#include "student.h"
#include "employee.h"

class Intern : public Employee, public Student
{
	protected:
		int period;
	public:
		Intern(const char *name = "", int id = 0, const char* position = "", 
			int salary = 0, int fn = 0, int grade = 0, int period = 0);

	void print() const;
};

#endif
