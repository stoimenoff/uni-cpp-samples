#ifndef _HOURLY_WORKER_H_
#define _HOURLY_WORKER_H_

#include "worker.h"
#include <iostream>

class HourlyWorker : public Worker
{
	private:
		int hoursWorked;
		char* workType;
		void init(int hoursWorked, const char* workType);
	public:
		HourlyWorker(const char *name = "", unsigned int hourPayment = 0, 
			int hoursWorked = 0, const char* workType = "");
		HourlyWorker(const HourlyWorker &other);
		HourlyWorker& operator = (const HourlyWorker &other);
		~HourlyWorker();

		void setWorkType(const char* workType);
		void setHoursWorked(const int hoursWorked);

		int getHoursWorked() const;
		const char * getWorkType() const;

		void print() const;

};

#endif
