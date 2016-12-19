#include "filetokenizer.h"
#include "stringtokenizer.h"
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


	cout << "==============" << endl;

	StringTokenizer stokenizer("token1,token2, token3 t4 tok5 tok6,  ", DELIMITERS);

	while(stokenizer.hasToken())
	{
		cout << stokenizer.getToken() << endl;
	}

	return 0;
}
