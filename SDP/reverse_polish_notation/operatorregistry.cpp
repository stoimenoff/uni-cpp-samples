#include "operatorregistry.h"

Operator OperatorRegistry::getOperatorFor(string symbol) const
{
	for(Operator operatr : operators)
	{
		if (operatr.getSymbol() == symbol)
		{
			return operatr;
		}
	}
	throw logic_error("No operator");
}

void OperatorRegistry::registerOperator(Operator operatr)
{
	if(hasOperatorFor(operatr.getSymbol()))
	{
		throw logic_error("Operator already exists");
	}
	operators.push_back(operatr);
}

bool OperatorRegistry::hasOperatorFor(string symbol) const
{
	try
	{
		getOperatorFor(symbol);
		return true;
	}
	catch(logic_error& e)
	{
		return false;
	}
}