#ifndef _FILETOKENIZER_H_
#define _FILETOKENIZER_H_

#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::ifstream;
using std::getline;

class FileTokenizer
{
	public:
		FileTokenizer(const string& filename, const string& delimiters);
		string getToken();
		string peekToken();
		bool hasToken();
	private:
		string extractTokenFromStream();
		ifstream stream;
		string delimiters;
		string buffer;
		string preparedToken;
};

#endif
