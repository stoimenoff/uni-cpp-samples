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
		bool leftAssociative;
		string symbol;
		EvaluateFunction evaluateFunction;

	public:
		Operator(string symbol, int numberOfArguments, double priority,
				EvaluateFunction evaluateFunction)
			: symbol(symbol), numberOfArguments(numberOfArguments),
			priority(priority), evaluateFunction(evaluateFunction),
			leftAssociative(true) {}

		Operator(string symbol, int numberOfArguments, double priority,
				EvaluateFunction evaluateFunction, bool leftAssociative)
			: symbol(symbol), numberOfArguments(numberOfArguments),
			priority(priority), evaluateFunction(evaluateFunction),
			leftAssociative(leftAssociative) {}

		int getArgumentsCount() const {return numberOfArguments;}
		double getPriority() const {return priority;}
		bool isLeftAssociative() const {return leftAssociative;}
		string getSymbol() const {return symbol;}
		double evaluate(vector<double> arguments) const;

		bool operator == (const Operator& other) const;

		bool operator != (const Operator& other) const;
};

#endif
