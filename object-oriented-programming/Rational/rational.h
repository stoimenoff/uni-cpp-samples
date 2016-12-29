#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <iostream>
#include <cmath>

class Rational
{
	public:
		/*Constructors*/
		Rational (int numerator = 0, int denominator = 1);
		Rational (Rational const &other);
		/*Arithmetic operators*/
		Rational operator + (Rational const &other) const;
		Rational operator * (Rational const &other) const;
		Rational operator - (Rational const &other) const;
		Rational operator - () const;
		Rational operator / (Rational const &other) const;
		Rational operator ^ (unsigned int const &power) const;
		/*Modifying operators*/
		Rational& operator = (Rational const &other);
		Rational& operator += (Rational const &other);
		Rational& operator -= (Rational const &other);
		Rational& operator *= (Rational const &other);
		Rational& operator /= (Rational const &other);
		Rational& operator ^= (unsigned int const &power);
			//prefix
		Rational& operator ++ ();
		Rational& operator -- ();
			//postfix
		Rational operator ++ (int);
		Rational operator -- (int);
		/*Comparison operators*/
		bool operator < (Rational const &other) const;
		bool operator > (Rational const &other) const;
		bool operator <= (Rational const &other) const;
		bool operator >= (Rational const &other) const;
		bool operator == (Rational const &other) const;
		bool operator != (Rational const &other) const;
		/*Stream operators*/
		friend std::ostream& operator << (std::ostream &stream, Rational const &number);
		friend std::istream& operator >> (std::istream &stream, Rational &number);
	private:
		int numerator;
		unsigned int denominator;
		void normalize ();
};
/*Reverse arithmeric operators for integers*/
Rational operator + (int const &number, Rational const &rational);
Rational operator - (int const &number, Rational const &rational);
Rational operator * (int const &number, Rational const &rational);
Rational operator / (int const &number, Rational const &rational);

#endif