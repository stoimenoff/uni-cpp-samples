#include "polynom.h"
/*Private helper functions*/
void Polynom::setDegreeAndAllocate(int degree)
{
	this->degree = degree;
	coefficients = new double[degree + 1];	
}

void Polynom::copyCoeffs(int degree, const double coefficients[])
{
	setDegreeAndAllocate(degree);
	for (int i = 0; i < degree + 1; ++i)
	{
		this->coefficients[i] = coefficients[i];
	}
}

/*Constructors and assignment operator*/
Polynom::Polynom(int degree)
{
	setDegreeAndAllocate(degree);
}

Polynom::Polynom(int degree, double coefficients[])
{
	copyCoeffs(degree, coefficients);
}

Polynom::Polynom(const Polynom& other)
{
	copyCoeffs(other.degree, other.coefficients);
}

Polynom& Polynom::operator = (const Polynom& other)
{
	if (this != &other)
	{
		delete[] coefficients;
		copyCoeffs(other.degree, other.coefficients);
	}
	return *this;
}

Polynom::~Polynom()
{
	delete[] coefficients;
}

/*Interface functions*/
double Polynom::evaluate(double x) const
{
	double result = 0;
	for (int i = 0; i < degree + 1; ++i)
	{
		result += coefficients[i] * std::pow(x, i);
	}
	return result;
}

void Polynom::setCoef(int degree, double newCoef)
{
	coefficients[degree] = newCoef;
}

double Polynom::getCoef(int degree) const
{
	return coefficients[degree];
}

void Polynom::print() const
{
	for (int i = 0; i < degree; ++i)
	{
		std::cout << coefficients[i] << "*x^" << i << " + ";

	}
	std::cout << coefficients[degree] << "*x^" << degree << std::endl;
}

/*Bonus*/
double Polynom::operator () (double x) const
{
	return evaluate(x);
}

Polynom Polynom::operator + (const Polynom& other) const
{
	int minDegree = (degree < other.degree) ? degree : other.degree;
	int maxDegree = (degree > other.degree) ? degree : other.degree;
	Polynom result(maxDegree);
	for (int i = 0; i < minDegree + 1; ++i)
	{
		result.setCoef(i, coefficients[i] + other.coefficients[i]);
	}
	int coef;
	for (int i = minDegree + 1; i < maxDegree + 1; ++i)
	{
		if (degree == maxDegree)
		{
			coef = coefficients[i];
		}
		else
		{
			coef = other.coefficients[i];
		}
		result.setCoef(i, coef);	
	}
	return result;
}

Polynom Polynom::operator - () const
{
	Polynom result(degree);
	for (int i = 0; i < degree + 1; ++i)
	{
		result.setCoef(i, - coefficients[i]);
	}
	return result;
}

Polynom Polynom::operator - (const Polynom& other) const
{
	return *this + (-other);
}

Polynom Polynom::operator * (const Polynom& other) const
{
	Polynom result(degree + other.degree);
	int coef;
	for (int i = 0; i < degree + 1; ++i)
	{
		for (int j = 0; j < other.degree + 1; ++j)
		{
			coef = result.getCoef(i + j);
			coef += (coefficients[i] * other.coefficients[j]);
			result.setCoef(i + j, coef);
		}
	}
	return result;
}


Polynom& Polynom::operator += (const Polynom& other)
{
	return *this = (*this + other);
}

Polynom& Polynom::operator -= (const Polynom& other)
{
	return *this = (*this - other);
}

Polynom& Polynom::operator *= (const Polynom& other)
{
	return *this = (*this * other);
}

bool Polynom::operator == (const Polynom& other) const
{
	if (degree != other.degree)
	{
		return false;
	}
	for (int i = 0; i < degree + 1; ++i)
	{
		if (coefficients[i] != other.coefficients[i])
		{
			return false;
		}
	}
	return true;
}

bool Polynom::operator != (const Polynom& other) const
{
	return !(*this == other);
}

std::ostream& operator << (std::ostream& out, const Polynom& polynom)
{
	for (int i = 0; i < polynom.degree; ++i)
	{
		out << polynom.coefficients[i] << "*x^" << i << " + ";
	}
	out << polynom.coefficients[polynom.degree] << "*x^" << polynom.degree << std::endl;
	return out;
}
std::istream& operator >> (std::istream& in, Polynom& polynom)
{
	for (int i = 0; i < polynom.degree + 1; ++i)
	{
		std::cout << "Enter coefficient for " << i << " degree: ";
		in >> polynom.coefficients[i];
	}
	return in;
}