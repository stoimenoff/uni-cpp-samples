#include "datetime.h"
const string DateTime::WEEKDAYS[] = {"Sunday", "Monday", "Tuesday",
				"Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

bool DateTime::validateDateString(string date)
{
	if (date.size() != 8)
		return false;
	for (int i = 0; i < 8; ++i)
	{
		if (i == 2 || i == 5)
		{
			if (date[i] != '.')
				return false;
		}
		else
		{
			if(date[i] < 48 || date[i] > 57)
				return false;
		}
	}
	return true;
}

bool DateTime::validateTimeString(string timeStr)
{
	if(timeStr.size() != 5)
		return false;
	for (int i = 0; i < 5; ++i)
	{
		if (i == 2)
		{
			if (timeStr[i] != ':')
				return false;
		}
		else
		{
			if(timeStr[i] < 48 || timeStr[i] > 57)
				return false;
		}
	}
	return true;
}

bool DateTime::validateIntervalString(string interval)
{
	for (int i = 0; i < interval.size(); ++i)
	{
		if(interval[i] < 48 || interval[i] > 57)
			return false;
	}
	int i = stoi(interval);
	if(i % 30 != 0 || i <= 0)
		return false;
	return true;
}

bool DateTime::isWeekDay(string day)
{
	for(string weekday : WEEKDAYS)
		if(weekday == day)
			return true;
	return false;
}

tm DateTime::getTm() const
{
	tm timeinfo = {};
	timeinfo.tm_year = year - 1900;
	timeinfo.tm_mon = month - 1;
	timeinfo.tm_mday = day;	
	return timeinfo;
}

DateTime::DateTime(int year, int month, int day, int hour, int minutes)
	: year(year), month(month), day(day), hour(hour), minutes(minutes) {}

DateTime::DateTime(string date)
	: year(2000), month(1), day(1), hour(8), minutes(0)
{
	if(validateDateString(date))
	{
		year = stoi(date.substr(6, 2)) + 2000;
		month = stoi(date.substr(3, 2));
		day = stoi(date.substr(0, 2));
	}
}

bool DateTime::isValid() const
{
	tm timeinfo = getTm();
	tm timeinfoCopy = timeinfo;
	mktime(&timeinfo);
	return (timeinfo.tm_mday == timeinfoCopy.tm_mday
			&& timeinfo.tm_mon == timeinfoCopy.tm_mon
			&& timeinfo.tm_year == timeinfoCopy.tm_year);
}

bool DateTime::isTimeValid() const
{
	return (hour >= 8 && hour <= 19
			&& minutes >= 0 && minutes <= 59);
}

string DateTime::getWeekday() const
{
	if (!isValid())
	{
		return "Invalid date";
	}
	tm timeinfo = getTm();
	mktime(&timeinfo);
	return WEEKDAYS[timeinfo.tm_wday];
}

DateTime DateTime::operator+ (int duration) const
{
	int newHour = hour + duration / 60;
	int newMinutes = minutes + duration % 60;
	if(newMinutes >= 60)
	{
		newMinutes -= 60;
		newHour += 1;
	}
	return DateTime(year, month, day, newHour, newMinutes);
}

void DateTime::setTime(string time)
{
	if(validateTimeString(time))
	{
		hour = stoi(time.substr(0, 2));
		minutes = stoi(time.substr(3, 2));
	}
}

void DateTime::setTime(int hour, int minutes)
{
	this->hour = hour;
	this->minutes = minutes;
}

bool DateTime::operator == (const DateTime &other) const
{
	return (year == other.year
			&& month == other.month
			&& day == other.day
			&& hour == other.hour
			&& minutes == other.minutes);
}
bool DateTime::operator != (const DateTime &other) const
{
	return !(*this == other);
}
bool DateTime::operator > (const DateTime &other) const
{
	if (year < other.year)
		return false;
	if (year > other.year)
		return true;
	//equal year
	if (month < other.month)
		return false;
	if (month > other.month)
		return true;
	//equal year and month
	if (day < other.day)
		return false;
	if (day > other.day)
		return true;
	//equal year, month and day
	if (hour < other.hour)
		return false;
	if (hour > other.hour)
		return true;
	return minutes > other.minutes;
}
bool DateTime::operator < (const DateTime &other) const
{
	return ((*this != other) && !(*this > other));
}
bool DateTime::operator >= (const DateTime &other) const
{
	return !(*this < other);
}
bool DateTime::operator <= (const DateTime &other) const
{
	return !(*this > other);
}

int DateTime::compareHours(const DateTime &other) const
{
	if(hour > other.hour)
		return -1;
	if(hour < other.hour)
		return 1;
	//equal hour
	if(minutes > other.minutes)
		return -1;
	if(minutes < other.minutes)
		return 1;
	return 0;
}