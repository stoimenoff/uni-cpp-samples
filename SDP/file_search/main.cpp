#include "tokenizer.h"
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;

int main()
{

	const string DELIMITERS = " ,.\n";
	FileTokenizer tokenizer("test", DELIMITERS);

	while(tokenizer.hasToken())
	{
		cout << tokenizer.getToken() << endl;
	}
	return 0;
}
