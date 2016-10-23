#include <iostream>
#include <stack>
#include <queue>
#include <cmath>

using std::stack;
using std::queue;

#include "operatorregistry.h"
#include "tokenizer.h"

double toNumber(string numberString)
{
	return std::stod(numberString);
}

double factorial(double n)
{
	return (n <= 1) ? 1 : n * factorial(n - 1);
}

void registerOperatorsIn(OperatorRegistry& operatorsRegistry)
{
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

	Operator power("^", 2, 10, [](vector<double> args){return pow(args[0], args[1]);});
	operatorsRegistry.registerOperator(power);
}

bool shouldPopOperatorsStack(const stack<Token>& operators, const Token& operatorToken, const OperatorRegistry& operatorsRegistry)
{
	if (operators.empty())
		return false;

	if (operators.top().value == "(")
		return false;

	Operator topOperator = operatorsRegistry.getOperatorFor(operators.top().value);
	Operator candidateOperator = operatorsRegistry.getOperatorFor(operatorToken.value);

	if(topOperator.getPriority() > candidateOperator.getPriority())
		return true;

	if(topOperator.getPriority() == candidateOperator.getPriority() && topOperator != candidateOperator)
		return true;
	
	return false;
}

queue<Token> getReversedPolishNotationOf(string input, const OperatorRegistry& operatorsRegistry)
{
	Tokenizer tokenizer(input);

	queue<Token> reversedPolishNotation;
	stack<Token> operators;

	Token token;
	while(tokenizer.present()) 
	{
		token = tokenizer.get();
		// std::cout << "|" << token.value << "|" << std::endl;
		if(token.isNumber)
		{
			tokenizer.forbidNegativeNumbers();
			reversedPolishNotation.push(token);
		}
		else if(operatorsRegistry.hasOperatorFor(token.value))
		{
			if(token.value == "-")
			{
				tokenizer.allowNegativeNumbers();
			}
			while(shouldPopOperatorsStack(operators, token, operatorsRegistry))
			{
				reversedPolishNotation.push(operators.top());
				operators.pop();
			}
			operators.push(token);
		}
		else if(token.value == "(")
		{
			operators.push(token);
		}
		else if(token.value == ")")
		{
			while(!operators.empty() && operators.top().value != "(")
			{
				reversedPolishNotation.push(operators.top());
				operators.pop();
			}
			operators.pop(); //remove (
		}
		else
		{
			throw logic_error("Unrecognized symbol " + token.value);
		}
	}
	while(!operators.empty())
	{
		reversedPolishNotation.push(operators.top());
		operators.pop();
	}
	return reversedPolishNotation;
}

double evaluateReversedPolishNotation(queue<Token>& reversedPolishNotation, const OperatorRegistry& operatorsRegistry)
{
	Token token;
	stack<double> numbers;
	while(!reversedPolishNotation.empty())
	{
		token = reversedPolishNotation.front();
		reversedPolishNotation.pop();
		if(operatorsRegistry.hasOperatorFor(token.value))
		{
			Operator operatr = operatorsRegistry.getOperatorFor(token.value);
			vector<double> operands;
			for (int i = 0; i < operatr.getArgumentsCount(); ++i)
			{
				if(numbers.empty())
				{
					throw logic_error("Not enough operands");
				}
				operands.insert(operands.begin(), numbers.top());
				numbers.pop();
			}
			numbers.push(operatr.evaluate(operands));
		}
		else
		{
			numbers.push(toNumber(token.value));
		}
	}

	if(numbers.size() != 1)
	{
		throw logic_error("Evaluaton error: More than one number in numbers stack at the end");
	}
	return numbers.top();
}

int main()
{
	string input;
	std::getline(std::cin, input);

	OperatorRegistry operatorsRegistry;
	registerOperatorsIn(operatorsRegistry);

	queue<Token> reversedPolishNotation = getReversedPolishNotationOf(input, operatorsRegistry);
	double value = evaluateReversedPolishNotation(reversedPolishNotation, operatorsRegistry);
	std::cout << value << std::endl;

	return 0;
}

