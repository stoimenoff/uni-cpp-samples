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

double factorial(double n)
{
	return (n <= 1) ? 1 : n * factorial(n - 1);
}

OperatorRegistry OperatorRegistry::Default()
{
	OperatorRegistry operatorsRegistry;
	Operator plus("+", 2, 5, [](vector<double> args){return args[0] + args[1];});
	operatorsRegistry.registerOperator(plus);

	Operator minus("-", 2, 5, [](vector<double> args){return args[0] - args[1];});
	operatorsRegistry.registerOperator(minus);

	Operator mult("*", 2, 6, [](vector<double> args){return args[0] * args[1];});
	operatorsRegistry.registerOperator(mult);

	Operator division("/", 2, 6, [](vector<double> args){return args[0] / args[1];});
	operatorsRegistry.registerOperator(division);

	Operator fact("!", 1, 11, [](vector<double> args){return factorial(args[0]);});
	operatorsRegistry.registerOperator(fact);

	Operator power("^", 2, 10, [](vector<double> args){return pow(args[0], args[1]);}, false);
	operatorsRegistry.registerOperator(power);

	return operatorsRegistry;
}
