#ifndef _PERSON_H_
#define _PERSON_H_

#include <iostream>
#include <cstring>

class Person
{
	protected:
		char *name;
		int id;
		void init(const char* name, int id);

	public:
		Person(const char* name = "", int id = 0);
		Person(const Person &other);
		Person& operator = (const Person &other);
		~Person();

		void print() const;
};

#endif
