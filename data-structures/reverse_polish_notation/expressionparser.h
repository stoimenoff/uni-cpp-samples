#ifndef _EXPRESSIONPARSER_H_
#define _EXPRESSIONPARSER_H_

#include <stack>
#include <queue>
#include <cmath>
#include <iostream>

#include "operatorregistry.h"
#include "tokenizer.h"

using std::stack;
using std::queue;
using std::stod;

class ExpressionParser
{
	private:
		OperatorRegistry operatorsRegistry;
		bool shouldPopOperatorsStack(const stack<string>& operators, const string& operatr) const;
	public:
		ExpressionParser();
		ExpressionParser(const OperatorRegistry& operatorsRegistry);
		queue<string> getQueueReversedPolishNotationOf(const string& expression) const;
		stack<string> getStackReversedPolishNotationOf(const string& expression) const;
		double evaluate(const string& expression) const;
		OperatorRegistry getOperatorsRegistry() const;
};

#endif // _EXPRESSIONPARSER_H_