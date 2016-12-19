#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "filetokenizer.h"
#include "stringtokenizer.h"

using std::cin;
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

void printFileSet(const unordered_set<string>& filenames)
{
	for(const string& filename : filenames)
	{
		cout << filename << endl;
	}
}

void printTokens(unordered_map<string, unordered_set<string>> tokensRegistry)
{
	for(const pair<string, unordered_set<string>>& entry : tokensRegistry)
	{
		cout << "Token: \"" << entry.first << "\" found in files:" << endl;
		printFileSet(entry.second);
	}
}

pair<vector<string>, string> parseArguments(int argc, char* argv[])
{
	const string DEFAULT_DELIMITERS = " ,.\n:";
	vector<string> filesnames;
	string delimiters;
	for (int i = 1; i < argc; ++i)
	{
		// cout << argv[i] << endl;
		if (string(argv[i]) == "-d" || string(argv[i]) == "-dnst")
		{
			delimiters += argv[i + 1];
			if(string(argv[i]) == "-dnst")
				delimiters += " \n\t";
			++i; // skip next argument, because it's delimiters
		}
		else if(string(argv[i]) == "-nst")
		{
			delimiters += " \n\t";
		}
		else if(string(argv[i]) == "-n")
		{
			delimiters += '\n';
		}
		else if(string(argv[i]) == "-s")
		{
			delimiters += ' ';
		}
		else if(string(argv[i]) == "-t")
		{
			delimiters += '\t';
		}
		else
		{
			filesnames.push_back(string(argv[i]));
		}
	}
	if(delimiters.empty())
		delimiters = DEFAULT_DELIMITERS;
	return make_pair(filesnames, delimiters);
}

void serveQuery(string query, const string& delimiters,
		unordered_map<string, unordered_set<string>>& tokensRegistry)
{
	StringTokenizer queryTokens(query, delimiters);
	string token;
	while(queryTokens.hasToken())
	{
		token = queryTokens.getToken();
		if(tokensRegistry.find(token) != tokensRegistry.end())
		{
			cout << "Token: \"" << token << "\" found in files:" << endl;
			printFileSet(tokensRegistry[token]);
		}
	}
}

int main(int argc, char* argv[])
{
	auto arguments = parseArguments(argc, argv);
	vector<string> filesnames = arguments.first;
	string delimiters = arguments.second;

	auto tokensRegistry = filesTokens(filesnames, delimiters);
	printTokens(tokensRegistry);

	string query;
	do
	{
		getline(cin, query);
		serveQuery(query, delimiters, tokensRegistry);
	}
	while (!query.empty());

	return 0;
}
