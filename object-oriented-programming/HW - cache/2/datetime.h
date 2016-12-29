#ifndef _DATETIME_H_
#define _DATETIME_H_

#include <ctime>
#include <string>
using std::string;

class DateTime
{
	private:
		int year;
		int month;
		int day;
		int hour;
		int minutes;
		tm getTm() const;
	public:
		static const string WEEKDAYS[];
		static bool validateDateString(string date);
		static bool validateTimeString(string time);
		static bool validateIntervalString(string interval);
		static bool isWeekDay(string day);

		DateTime(int year = 2000, int month = 1, int day = 1, int hour = 8,
				int minutes = 0);
		DateTime(string date);
		int getYear() const {return year;}
		int getMonth() const {return month;}
		int getDay() const {return day;}
		int getHour() const {return hour;}
		int getMinutes() const {return minutes;}
		void setTime(string time);
		void setTime(int hour, int minutes);

		DateTime operator+ (int minutes) const;

		bool operator == (const DateTime &other) const;
		bool operator != (const DateTime &other) const;
		bool operator > (const DateTime &other) const;
		bool operator < (const DateTime &other) const;
		bool operator >= (const DateTime &other) const;
		bool operator <= (const DateTime &other) const;

		string getWeekday() const;
		bool isValid() const;
		bool isTimeValid() const;

		bool timeIsInvalid() const {return !isTimeValid();}
		int compareHours(const DateTime &other) const;
};

#endif