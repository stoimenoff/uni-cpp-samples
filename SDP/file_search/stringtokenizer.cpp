#include "stringtokenizer.h"

StringTokenizer::StringTokenizer(const string& tokens, const string& delimiters)
 	: tokens(tokens), delimiters(delimiters)
	{
		preparedToken = extractToken();
	}

bool StringTokenizer::isDelimiter(const char c) const
{
	return delimiters.find(c) != string::npos;
}

void StringTokenizer::eraseTrailingDelimiters()
{
	while(isDelimiter(tokens.front()))
		tokens.erase(0, 1);
}

string StringTokenizer::extractToken()
{
	eraseTrailingDelimiters();
	size_t firstDelimiterIndex = tokens.find_first_of(delimiters);
	string result = tokens.substr(0, firstDelimiterIndex);
	tokens.erase(0, firstDelimiterIndex);
	return result;
}

string StringTokenizer::getToken()
{
	string result = preparedToken;
	preparedToken = extractToken();
	return result;
}

string StringTokenizer::peekToken()
{
	return preparedToken;
}

bool StringTokenizer::hasToken()
{
	peekToken();
	return !preparedToken.empty();
}

string StringTokenizer::getDelimiters() const
{
	return delimiters;
}
