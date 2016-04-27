#include <iostream>

class Person
{
	protected:
		char *name;
		int id;
		void init(const char* name, int id);

	public:
		Person(const char* name = "", int id = 0);
		Person(const Person &other);
		Pesron& operator = (const Person &other);
		~Person();

		void print() const;
};
