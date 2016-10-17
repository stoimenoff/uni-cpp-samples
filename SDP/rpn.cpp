#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <stack>
#include <queue>
#include <cmath>

using std::vector;
using std::string;
using std::stack;
using std::queue;
using std::logic_error;

using EvaluateFunction = double (*) (vector<double> arguments);

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
		double evaluate(vector<double> arguments) const
		{
			if(arguments.size() != numberOfArguments)
			{
				throw logic_error("Invalid number of arguments");
			}
			return evaluateFunction(arguments);
		}

		bool operator == (const Operator& other) const
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

		bool operator != (const Operator& other) const
		{
			return !(*this == other);
		}
};

class OperatorRegistry
{
	private:
		vector<Operator> operators;
	public:
		Operator getOperatorFor(string symbol)
		{
			for(Operator& operatr : operators)
			{
				if (operatr.getSymbol() == symbol)
				{
					return operatr;
				}
			}
			throw logic_error("No operator");
		}

		void registerOperator(Operator operatr)
		{
			if(hasOperatorFor(operatr.getSymbol()))
			{
				throw logic_error("Operator already exists");
			}
			operators.push_back(operatr);
		}

		bool hasOperatorFor(string symbol)
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
};

struct Token
{
	Token() {};
	Token(string value, bool isNumber) : value(value), isNumber(isNumber) {}
	string value;
	bool isNumber;
};

class Tokenizer
{
	private:
		string input;

		bool isDigit(char c)
		{
			return (c >= 48 && c <= 57);
		}
		string getNumber()
		{
			string number = "";
			while(input.length() > 0 && (isDigit(input.front()) || input.front() == '.'))
			{
				number.append(input.substr(0, 1));
				input.erase(0, 1);
			}
			return number;
		}
		void removeBeginningWhitespaces()
		{
			while(input.length() > 0 && input.front() == ' ')
			{
				input.erase(0, 1);
			}
		}
	public:
		Tokenizer(string input) : input(input) {}
		Token get()
		{
			removeBeginningWhitespaces();
			if(!present())
			{
				throw logic_error("End of input");
			}
			char symbol = input.front();
			if(isDigit(symbol))
			{
				return Token(getNumber(), true);
			}
			input.erase(0, 1);
			return Token(string(1, symbol), false);
		}
		bool present()
		{
			removeBeginningWhitespaces();
			return !input.empty();
		}
};

double toNumber(string numberString)
{
	return std::stod(numberString);
}


double factorial(double n)
{
	return (n <= 1) ? 1 : n * factorial(n - 1);
}

int main()
{
	string input;
	std::getline(std::cin, input);
	
	Tokenizer tokenizer(input);
	bool expectOperator = false;
	bool expectNegativeNumber = false;

	OperatorRegistry operatorsRegistry;
	Operator plus("+", 2, 5, [](vector<double> args){return args[0] + args[1];});
	operatorsRegistry.registerOperator(plus);

	Operator minus("-", 2, 5, [](vector<double> args){return args[0] - args[1];});
	operatorsRegistry.registerOperator(minus);

	Operator mult("*", 2, 6, [](vector<double> args){return args[0] * args[1];});
	operatorsRegistry.registerOperator(mult);

	Operator division("/", 2, 6, [](vector<double> args){return args[0] / args[1];});
	operatorsRegistry.registerOperator(division);

	Operator fact("!", 1, 10, [](vector<double> args){return factorial(args[0]);});
	operatorsRegistry.registerOperator(fact);

	Operator power("^", 2, 11, [](vector<double> args){return pow(args[0], args[1]);});
	operatorsRegistry.registerOperator(power);

	queue<Token> reversedPolishNotation;
	stack<Token> operators;

	Token token;
	while(tokenizer.present()) 
	{
		token = tokenizer.get();
		std::cout << "|" << token.value << "|" << std::endl;
		if(token.isNumber)
		{
			if(expectNegativeNumber)
			{
				token.value.insert(0, "-");
				reversedPolishNotation.push(token);
				expectNegativeNumber = false;
			}
			else
			{
				reversedPolishNotation.push(token);
			}
			expectOperator = true;
		}
		else
		{
			if(operatorsRegistry.hasOperatorFor(token.value))
			{
				if(!expectOperator && token.value == "-")
				{
					expectNegativeNumber = true;
					continue;
				}
				Operator operatr = operatorsRegistry.getOperatorFor(token.value);
				double priority = operatr.getPriority();
				while(!operators.empty() && operators.top().value != "(")
				{
					Operator topOperator = operatorsRegistry.getOperatorFor(operators.top().value);
					if(topOperator.getPriority() > priority)
					{
						reversedPolishNotation.push(operators.top());
						operators.pop();
					}
					else if(topOperator.getPriority() == priority && topOperator != operatr)
					{
						reversedPolishNotation.push(operators.top());
						operators.pop();
					}
					else
					{
						break;
					}
				}
				operators.push(token);
				expectOperator = false;
			}
			else // no operator
			{
				if(token.value == "(")
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
					throw logic_error("Unrecognized symbol");
				}
			}
		}
	}

	while(!operators.empty())
	{
		reversedPolishNotation.push(operators.top());
		operators.pop();
	}

	/*==============Evaluate================*/

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

	std::cout << numbers.top() << std::endl;

	return 0;
}

