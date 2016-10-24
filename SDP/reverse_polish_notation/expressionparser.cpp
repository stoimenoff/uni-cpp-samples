#include "expressionparser.h"

ExpressionParser::ExpressionParser(const OperatorRegistry& operatorsRegistry)
									: operatorsRegistry(operatorsRegistry) {}

ExpressionParser::ExpressionParser() : operatorsRegistry(OperatorRegistry::Default()) {};

bool ExpressionParser::shouldPopOperatorsStack(const stack<string>& operators, const string& operatr) const
{
	if (operators.empty())
		return false;

	if (operators.top() == "(")
		return false;

	Operator topOperator = operatorsRegistry.getOperatorFor(operators.top());
	Operator candidateOperator = operatorsRegistry.getOperatorFor(operatr);

	if(topOperator.getPriority() > candidateOperator.getPriority())
		return true;

	if(topOperator.getPriority() == candidateOperator.getPriority() && topOperator != candidateOperator)
		return true;
	
	return false;
}

queue<string> ExpressionParser::getQueueReversedPolishNotationOf(const string& expression) const
{
	Tokenizer tokenizer(expression);

	queue<string> reversedPolishNotation;
	stack<string> operators;

	Token token;
	while(tokenizer.present()) 
	{
		token = tokenizer.get();
		// std::cout << "|" << token.value << "|" << std::endl;
		if(token.isNumber)
		{
			tokenizer.forbidNegativeNumbers();
			reversedPolishNotation.push(token.value);
		}
		else if(operatorsRegistry.hasOperatorFor(token.value))
		{
			if(token.value == "-")
			{
				tokenizer.allowNegativeNumbers();
			}
			while(shouldPopOperatorsStack(operators, token.value))
			{
				reversedPolishNotation.push(operators.top());
				operators.pop();
			}
			operators.push(token.value);
		}
		else if(token.value == "(")
		{
			operators.push(token.value);
		}
		else if(token.value == ")")
		{
			while(!operators.empty() && operators.top() != "(")
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

stack<string> ExpressionParser::getStackReversedPolishNotationOf(const string& expression) const
{
	queue<string> tokensQueue = getQueueReversedPolishNotationOf(expression);
	stack<string> tokens;
	while(!tokensQueue.empty())
	{
		tokens.push(tokensQueue.front());
		tokensQueue.pop();
	}
	return tokens;
}

double ExpressionParser::evaluate(const string& expression) const
{
	queue<string> reversedPolishNotation = getQueueReversedPolishNotationOf(expression);
	string token;
	stack<double> numbers;
	while(!reversedPolishNotation.empty())
	{
		token = reversedPolishNotation.front();
		reversedPolishNotation.pop();
		if(operatorsRegistry.hasOperatorFor(token))
		{
			Operator operatr = operatorsRegistry.getOperatorFor(token);
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
			numbers.push(stod(token));
		}
	}

	if(numbers.size() != 1)
	{
		throw logic_error("Evaluaton error: More than one number in numbers stack at the end");
	}
	return numbers.top();
}

OperatorRegistry ExpressionParser::getOperatorsRegistry() const
{
	return operatorsRegistry;
}
