#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "filetokenizer.h"
#include "stringtokenizer.h"

using std::cout;
using std::endl;
using std::vector;
using std::unordered_set;
using std::unordered_map;
using std::pair;
using std::make_pair;

unordered_set<string> fileTokens(const string& filename, const string& delimiters)
{
	unordered_set<string> tokens;
	FileTokenizer tokenizer(filename, delimiters);
	while(tokenizer.hasToken())
		tokens.insert(tokenizer.getToken());
	return tokens;
}

unordered_map<string, unordered_set<string>> filesTokens(const vector<string>& filenames, const string& delimiters)
{
	unordered_map<string, unordered_set<string>> allTokens;
	for(const string& filename : filenames)
	{
		for(const string& token : fileTokens(filename, delimiters))
		{
			if(allTokens.find(token) == allTokens.end())
			{
				allTokens.insert(make_pair(token, unordered_set<string>()));
			}
			allTokens[token].insert(filename);
		}
	}
	return allTokens;
}

int main()
{
	const string DELIMITERS = " ,.\n:";
	vector<string> filesnames = {"test", "file1.txt", "file2.txt",
								"file3.txt", "file4.txt"};

	for(const pair<string, unordered_set<string>>& entry : filesTokens(filesnames, DELIMITERS))
	{
		cout << "Token: \"" << entry.first << "\" found in files:" << endl;
		for(const string& filename : entry.second)
		{
			cout << filename << endl;
		}
	}


	return 0;
}
