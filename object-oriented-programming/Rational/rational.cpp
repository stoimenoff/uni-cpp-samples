#include "rational.h"

void Rational::normalize ()
{
	for (int i = 2; i <= denominator; ++i)
	{
		while (numerator % i == 0 &&denominator % i == 0)
		{
			numerator /= i;
			denominator /= i;
		}
	}
}

/*Constructors*/
Rational::Rational (int numerator, int denominator)
{
	denominator = (denominator == 0) ? 1 : denominator;

	int sign = (numerator == 0) ? 1 : (numerator*denominator) / std::abs(numerator*denominator);

	this->numerator = sign * std::abs(numerator);
	this->denominator = std::abs(denominator);
	normalize();
}

Rational::Rational (Rational const &other)
{
	this->numerator = other.numerator;
	this->denominator = other.denominator;
}

/*Arithmetic operators*/
Rational Rational::operator + (Rational const &other) const
{

	int new_num = other.denominator*numerator + denominator*other.numerator;
	int new_denom = denominator * other.denominator;
	return Rational(new_num, new_denom);
}

Rational Rational::operator * (Rational const &other) const
{

	int new_num = numerator * other.numerator;
	int new_denom = denominator * other.denominator;
	return Rational(new_num, new_denom);
}

Rational Rational::operator - (Rational const &other) const
{
	return *this + (other * -1);
}

Rational Rational::operator - () const
{
	return Rational(-numerator, denominator);
}

Rational Rational::operator / (Rational const &other) const
{
	return *this * Rational(other.denominator, other.numerator);
}

Rational Rational::operator ^ (unsigned int const &power) const
{
	int new_num = pow(numerator, power);
	int new_denom = pow(denominator, power);
	return Rational(new_num, new_denom);
}

/*Modifying operators*/
Rational& Rational::operator = (Rational const &other)
{
	numerator = other.numerator;
	denominator = other.denominator;
	return *this;
}

Rational& Rational::operator += (Rational const &other)
{
	return *this = *this + other;
}

Rational& Rational::operator -= (Rational const &other)
{
	return *this = *this - other;
}

Rational& Rational::operator *= (Rational const &other)
{
	return *this = *this * other;
}

Rational& Rational::operator /= (Rational const &other)
{
	return *this = *this / other;
}

Rational& Rational::operator ^= (unsigned int const &power)
{
	return *this = *this ^ power;
}

//prefix
Rational& Rational::operator ++ ()
{
	return *this += 1;
}

Rational& Rational::operator -- ()
{
	return *this -= 1;
}

//postfix
Rational Rational::operator ++ (int)
{
	Rational copy = *this;
	++*this;
	return copy;
}

Rational Rational::operator -- (int)
{
	Rational copy = *this;
	--*this;
	return copy;
}

/*Comparison operators*/
bool Rational::operator < (Rational const &other) const
{
	return (*this - other).numerator < 0;
}

bool Rational::operator > (Rational const &other) const
{
	return other < *this;
}

bool Rational::operator <= (Rational const &other) const
{
	return !(*this > other);
}

bool Rational::operator >= (Rational const &other) const
{
	return !(*this < other);
}

bool Rational::operator == (Rational const &other) const
{
	return numerator == other.numerator && denominator == other.denominator;
}

bool Rational::operator != (Rational const &other) const
{
	return !(*this == other);
}

/*Stream operators*/
std::ostream& operator << (std::ostream &stream, Rational const &number)
{
	stream << number.numerator << "/" << number.denominator;
	return stream;
}

std::istream& operator >> (std::istream &stream, Rational &number)
{
	int num, denom;
	stream >> num >> denom;
	number = Rational(num, denom);
	return stream;
}

/*Reverse arithmeric operators for integers*/
Rational operator + (int const &number, Rational const &rational)
{
	return rational + number;
}

Rational operator - (int const &number, Rational const &rational)
{
	return Rational(number) - rational;
}

Rational operator * (int const &number, Rational const &rational)
{
	return rational * number;
}

Rational operator / (int const &number, Rational const &rational)
{
	return Rational(number) / rational;
}
