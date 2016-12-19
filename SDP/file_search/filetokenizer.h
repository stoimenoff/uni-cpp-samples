#ifndef _FILETOKENIZER_H_
#define _FILETOKENIZER_H_

#include <string>
#include <iostream>
#include <fstream>

#include "stringtokenizer.h"

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
		void eraseTrailingDelimitersFromStream();
		void prepareBuffer();
		string getBufferFromStream();
		ifstream stream;
		string delimiters;
		StringTokenizer bufferTokenizer;

};

#endif
