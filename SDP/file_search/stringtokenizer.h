#ifndef _STRINGTOKENIZER_H_
#define _STRINGTOKENIZER_H_

#include <string>
#include <iostream>

using std::string;
using std::getline;

class StringTokenizer
{
	public:
		StringTokenizer(const string& tokens, const string& delimiters);
		string getToken();
		string peekToken();
		bool hasToken();
		bool isDelimiter(const char c) const;
		string getDelimiters() const;
	private:
		string extractToken();
		void eraseTrailingDelimiters();
		string tokens;
		string delimiters;
		string preparedToken;
};

#endif
