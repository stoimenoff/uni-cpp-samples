#include "tokenizer.h"

FileTokenizer::FileTokenizer(const string& filename, const string& delimiters)
 	: delimiters(delimiters)
{
	stream = ifstream(filename);
}

string FileTokenizer::extractTokenFromStream()
{
	if(buffer.empty())
		getline(stream, buffer, delimiters[0]);

	size_t firstDelimiterIndex = buffer.find_first_of(delimiters);

	string result = buffer.substr(0, firstDelimiterIndex);
	buffer.erase(0, firstDelimiterIndex);

	if(firstDelimiterIndex != string::npos)
	{
		buffer.erase(0, 1); //remove delimiter
	}
	return result;
}

string FileTokenizer::getToken()
{
	if(!preparedToken.empty())
	{
		string result = preparedToken;
		preparedToken.clear();
		return result;
	}
	return extractTokenFromStream();
}

string FileTokenizer::peekToken()
{
	if(preparedToken.empty())
		preparedToken = getToken();
	return preparedToken;
}

bool FileTokenizer::hasToken()
{
	peekToken();
	return !preparedToken.empty();
}
