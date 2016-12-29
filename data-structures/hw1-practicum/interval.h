#ifndef _INTERVAL_H_
#define _INTERVAL_H_

#include <iostream>
using std::ostream;

struct Interval
{
	double start;
	double end;
	Interval(double start = 0, double end = 0) : start(start), end(end) {}
};

double length(const Interval& interval)
{
	return interval.end - interval.start;
}

bool operator==(const Interval& first, const Interval& second)
{
	return length(first) == length(second);
}

bool operator!=(const Interval& first, const Interval& second)
{
	return !(first == second);
}

bool operator<(const Interval& first, const Interval& second)
{
	return length(first) < length(second);
}

bool operator<=(const Interval& first, const Interval& second)
{
	return first < second || first == second;
}

bool operator>(const Interval& first, const Interval& second)
{
	return !(first <= second);
}

bool operator>=(const Interval& first, const Interval& second)
{
	return !(first < second);
}

ostream& operator<< (ostream& out, const Interval& interval)
{
	out << "[" << interval.start << ", " << interval.end << "]";
}

#endif
