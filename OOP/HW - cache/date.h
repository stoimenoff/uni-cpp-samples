#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>

class Date
{
	private:
		int day, month, year;
		bool isDateValid(int day, int month, int year);
		bool leapYear(int year);
		bool corrupted;
	public:
		Date(int day = 1, int month = 1, int year = 1970);
		//Date(const Date &other);

		int Day() const {return day;}
		int Month() const {return month;}
		int Year() const {return year;}

		bool isCorrupted() const {return corrupted;}

		friend std::istream& operator >> (std::istream& in, Date& date);
};

std::ostream& operator << (std::ostream& out, const Date& date);

#endif
