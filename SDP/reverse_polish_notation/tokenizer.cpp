#include "tokenizer.h"

bool Tokenizer::isDigit(char c) const
{
	return (c >= 48 && c <= 57);
}

bool Tokenizer::isNumberBeginning(char c) const
{
	return isDigit(c) || (negativeNumbersAllowed && c == Tokenizer::MINUS);
}

string Tokenizer::toString(char c) const
{
	return string(1, c);
}

bool Tokenizer::isSymbolAllowedInNumber(char c, bool allowDelimiter) const
{
	return isDigit(c) || (allowDelimiter && c == Tokenizer::NUMBER_DELIMITER);
}

string Tokenizer::getNumber()
{
	string number = "";
	if(negativeNumbersAllowed && input.front() == Tokenizer::MINUS)
	{
		number.append(toString(Tokenizer::MINUS));
		removeInputFront();
	}
	bool delimiterNotUsed = true;
	while(input.length() > 0 && isSymbolAllowedInNumber(input.front(), delimiterNotUsed))
	{
		if(input.front() == Tokenizer::NUMBER_DELIMITER)
		{
			delimiterNotUsed = false;
		}
		number.append(toString(input.front()));
		removeInputFront();
	}
	return number;
}

char Tokenizer::removeInputFront()
{
	char front = input.front();
	input.erase(0, 1);
	return front;
}

void Tokenizer::removeBeginningWhitespaces()
{
	while(input.length() > 0 && input.front() == Tokenizer::WHITESPACE)
	{
		removeInputFront();
	}
}

Tokenizer::Tokenizer(string input) : input(input), negativeNumbersAllowed(true) {}

void Tokenizer::allowNegativeNumbers()
{
	negativeNumbersAllowed = true;
}

void Tokenizer::forbidNegativeNumbers()
{
	negativeNumbersAllowed = false;
}

Token Tokenizer::get()
{
	if(!present())
	{
		throw logic_error("End of input");
	}
	if(isNumberBeginning(input.front()))
	{
		return Token(getNumber(), true);
	}
	else
	{
		return Token(toString(removeInputFront()), false);
	}
}

bool Tokenizer::present()
{
	removeBeginningWhitespaces();
	return !input.empty();
}