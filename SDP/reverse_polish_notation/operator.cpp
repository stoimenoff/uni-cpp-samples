#include "operator.h"

double Operator::evaluate(vector<double> arguments) const
{
	if(arguments.size() != numberOfArguments)
	{
		throw logic_error("Invalid number of arguments");
	}
	return evaluateFunction(arguments);
}

bool Operator::operator==(const Operator& other) const
{
	if(symbol != other.symbol)
	{
		return false;
	}
	if(numberOfArguments != other.numberOfArguments)
	{
		return false;
	}
	if(priority != other.priority)
	{
		return false;
	}
	return true;
}

bool Operator::operator!=(const Operator& other) const
{
	return !(*this == other);
}