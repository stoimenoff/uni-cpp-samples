#ifndef __OPERATOR_H
#define __OPERATOR_H

#include <vector>
#include <string>
#include <stdexcept>

using std::vector;
using std::string;
using std::logic_error;

typedef double (*EvaluateFunction) (vector<double> arguments);

class Operator
{
	private:
		double priority;
		int numberOfArguments;
		string symbol;
		EvaluateFunction evaluateFunction;

	public:
		Operator(string symbol, int numberOfArguments, double priority, EvaluateFunction evaluateFunction)
			: symbol(symbol), numberOfArguments(numberOfArguments), priority(priority), evaluateFunction(evaluateFunction) {}

		int getArgumentsCount() const {return numberOfArguments;}
		double getPriority() const {return priority;}
		string getSymbol() const {return symbol;}
		double evaluate(vector<double> arguments) const;

		bool operator == (const Operator& other) const;

		bool operator != (const Operator& other) const;
};

#endif