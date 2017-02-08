#ifndef _PRINTINTG_H_
#define _PRINTINTG_H_

#include <list>
#include <vector>
#include <iostream>

using std::list;
using std::vector;
using std::ostream;

template <class T>
ostream& operator << (ostream& out, const list<T>& l)
{
	for (const T& element : l)
		out << element << " ";
	return out;
}

template <class T>
ostream& operator << (ostream& out, const vector<T>& v)
{
	for (const T& element : v)
		out << element << " ";
	return out;
}

#endif
