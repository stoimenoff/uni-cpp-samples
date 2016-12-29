#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <string>
#include <stdexcept>

using std::string;
using std::logic_error;

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
		static const char NUMBER_DELIMITER = '.';
		static const char WHITESPACE = ' ';
		static const char MINUS = '-';
		
		string input;
		bool negativeNumbersAllowed;

		bool isDigit(char c) const;
		bool isNumberBeginning(char c) const;
		bool isSymbolAllowedInNumber(char c, bool allowDelimiter = true) const;
		string toString(char c) const;
		string getNumber();
		char removeInputFront();
		void removeBeginningWhitespaces();
	public:
		Tokenizer(string input);
		Token get();
		bool present();

		void allowNegativeNumbers();
		void forbidNegativeNumbers();
};

#endif