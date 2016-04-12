#ifndef _POLYNOM_H_
#define _POLYNOM_H_

#include <cmath>
#include <iostream>

class Polynom
{
	public:
		/*Constructors and assignment operator*/
		Polynom(int degree = 0);
		Polynom(int degree, double coefficients[]);
		Polynom(const Polynom& other);
		Polynom& operator = (const Polynom& other);
		~Polynom();
		/*Interface functions*/
		double evaluate(double x) const;
		void setCoef(int degree, double newCoef);
		double getCoef(int degree) const;
		void print() const;

		/*Bonus*/
		double operator () (double x) const;
		Polynom operator + (const Polynom& other) const;
		Polynom operator - () const;
		Polynom operator - (const Polynom& other) const;
		Polynom operator * (const Polynom& other) const;
		
		Polynom& operator += (const Polynom& other);
		Polynom& operator -= (const Polynom& other);
		Polynom& operator *= (const Polynom& other);

		bool operator == (const Polynom& other) const;
		bool operator != (const Polynom& other) const;

		friend std::ostream& operator << (std::ostream& out, const Polynom& polynom);
		friend std::istream& operator >> (std::istream& in, Polynom& polynom);

	private:
		int degree;
		double* coefficients;
		void setDegreeAndAllocate(int degree);
		void copyCoeffs(int degree, const double coefficients[]);
};

#endif