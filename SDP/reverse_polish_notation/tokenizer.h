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
		string input;

		bool isDigit(char c);
		string getNumber();
		void removeBeginningWhitespaces();
	public:
		Tokenizer(string input);
		Token get();
		bool present();
};

#endif