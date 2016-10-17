#include "mystring.h"

void String::init(const char *str)
{
	buffer = new char[strlen(str) + 1];
	strcpy(buffer, str);
}

String::String(const char *str)
{
	init(str);
}

String::String(const String &other)
{
	init(other.buffer);
}

String::String(const Vector<char> &chars)
{
	buffer = new char[chars.Size() + 1];
	for (int i = 0; i < chars.Size(); ++i)
	{
		buffer[i] = chars[i];
	}
	buffer[chars.Size()] = 0;
}

String::String(int number)
{
	char numberStr [65];
	sprintf (numberStr, "%d", number);
	init(numberStr);
}

String::String(double number)
{
	char numberStr [65];
	sprintf (numberStr, "%f", number);
	init(numberStr);
}

String& String::operator = (const String &other)
{
	if (this != &other)
	{
		delete[] buffer;
		init(other.buffer);
	}
	return *this;
}

String& String::operator = (const char *str)
{
	delete[] buffer;
	init(str);
}

String::~String()
{
	delete[] buffer;
}

char& String::operator [] (unsigned int index)
{
	if (index >= strlen(buffer))
	{
		//exception
	}
	return buffer[index];
}

char String::operator [] (unsigned int index) const
{
	if (index >= strlen(buffer))
	{
		//exception
		return char(0);
	}
	return buffer[index];
}

String String::operator + (const String &other) const
{
	char *new_buffer = new char[strlen(buffer) + strlen(other.buffer) + 1];
	new_buffer[0] = 0;
	strcat(new_buffer, buffer);
	strcat(new_buffer, other.buffer);
	String result = new_buffer;
	delete[] new_buffer;
	return result;
}

String& String::operator += (const String &other)
{
	return *this = *this + other;
}

bool String::operator < (const String &other) const
{
	return strcmp(buffer, other.buffer) == -1;
}
bool String::operator > (const String &other) const
{
	return other < *this;
}
bool String::operator <= (const String &other) const
{
	return !(*this > other);
}
bool String::operator >= (const String &other) const
{
	return !(*this < other);
}
bool String::operator == (const String &other) const
{
	return strcmp(buffer, other.buffer) == 0;
}
bool String::operator != (const String &other) const
{
	return !(*this == other);
}

int String::length() const
{
	return strlen(buffer);
}

std::ostream& operator << (std::ostream& out, const String& string)
{
	for (int i = 0; i < string.length(); ++i)
	{
		out << string[i];
	}
	return out;
}

std::istream& operator >> (std::istream& in, String& string)
{
	Vector<char> input;
	char symbol;
	while (in.get(symbol) && symbol != '\n')
	{
		input.pushBack(symbol);
	}
	string = String(input);
	return in;
}