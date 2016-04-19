#include "date.h"

bool Date::leapYear(int year)
{
	return (year % 100 != 0 && year % 4 == 0) || (year % 400 == 0);
}

bool Date::isDateValid(int day, int month, int year)
{
	if (year < 1600 || year > 2100)
		return false;

	if (day < 1)
		return false;

	switch (month)
	{
		case 2:
			if(day > 29)
				return false;
			if(!leapYear(year) && day == 29)
				return false;
			break;
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if(day > 31)
				return false;
			break;
		case 4: case 6: case 9: case 11:
			if(day > 30)
				return false;
			break;
		default:
			return false;
			break;
	}
	return true;
}

Date::Date(int day, int month, int year)
{
	if (isDateValid(day, month, year))
	{
		this->day = day;
		this->month = month;
		this->year = year;
		corrupted = false;
	}
	else
	{
		this->day = 1;
		this->month = 1;
		this->year = 1970;
		corrupted = true;
	}
}
/*
Date::Date(const Date &other)
{
	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
}
*/
std::ostream& operator << (std::ostream& out, const Date& date)
{
	out << date.Day() << "." << date.Month() << "." << date.Year();
	return out;
}

std::istream& operator >> (std::istream& in, Date& date)
{
	int day, month, year;
	in >> day >> month >> year;
	date = Date(day, month, year);
}