#ifndef _WORKER_H_
#define _WORKER_H_

#include <cstring>
#include <iostream>

class Worker
{
	protected:
		char *name;
		unsigned int hourPayment;
		void init(const char *name, unsigned int hourPayment);
	public:
		Worker(const char *name = "", unsigned int hourPayment = 0);
		Worker(const Worker &other);
		Worker& operator = (const Worker &other);
		~Worker();

		unsigned int getHourPayment() const;
		const char* getName() const;

		void print() const;
};

#endif
