#include "filetokenizer.h"

FileTokenizer::FileTokenizer(const string& filename, const string& delimiters)
 	: delimiters(delimiters), bufferTokenizer("", delimiters)
{
	stream = ifstream(filename);
	prepareBuffer();
}

void FileTokenizer::eraseTrailingDelimitersFromStream()
{
	while(bufferTokenizer.isDelimiter(stream.peek()))
		stream.get();
}

string FileTokenizer::getBufferFromStream()
{
	eraseTrailingDelimitersFromStream();
	string buffer;
	getline(stream, buffer, delimiters.front());
	return buffer;
}

void FileTokenizer::prepareBuffer()
{
	if(!bufferTokenizer.hasToken())
		bufferTokenizer = StringTokenizer(getBufferFromStream(), delimiters);
}

string FileTokenizer::getToken()
{
	prepareBuffer();
	return bufferTokenizer.getToken();
}

string FileTokenizer::peekToken()
{
	prepareBuffer();
	return bufferTokenizer.peekToken();
}

bool FileTokenizer::hasToken()
{
	prepareBuffer();
	return bufferTokenizer.hasToken();
}
