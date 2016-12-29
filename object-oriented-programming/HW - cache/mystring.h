#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <iostream>
#include <fstream>

#include <cstdio>
#include <cstring>

#include "vector.h"

class String
{
	private:
		char *buffer;
		void init(const char *str);
	public:
		String(const char *str = "");
		String(const String &other);
		String(const Vector<char> &chars);
		String(int number);
		String(double number);
		String& operator = (const String &other);
		String& operator = (const char *str);
		~String();

		char& operator [] (unsigned int index);
		char operator [] (unsigned int index) const;

		String operator + (const String &other) const;
		String& operator += (const String &other);

		bool operator < (const String &other) const;
		bool operator > (const String &other) const;
		bool operator <= (const String &other) const;
		bool operator >= (const String &other) const;
		bool operator == (const String &other) const;
		bool operator != (const String &other) const;

		int length() const;

};

std::ostream& operator << (std::ostream& out, const String& string);
std::istream& operator >> (std::istream& in, String& string);

#endif //_STRING_H