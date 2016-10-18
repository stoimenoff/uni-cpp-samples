#include "tokenizer.h"

bool Tokenizer::isDigit(char c)
{
	return (c >= 48 && c <= 57);
}

string Tokenizer::getNumber()
{
	string number = "";
	while(input.length() > 0 && (isDigit(input.front()) || input.front() == '.'))
	{
		number.append(input.substr(0, 1));
		input.erase(0, 1);
	}
	return number;
}

void Tokenizer::removeBeginningWhitespaces()
{
	while(input.length() > 0 && input.front() == ' ')
	{
		input.erase(0, 1);
	}
}

Tokenizer::Tokenizer(string input) : input(input) {}

Token Tokenizer::get()
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

bool Tokenizer::present()
{
	removeBeginningWhitespaces();
	return !input.empty();
}