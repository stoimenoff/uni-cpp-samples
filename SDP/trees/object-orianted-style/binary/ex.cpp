#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include "tree.h"

using std::cout;
using std::string;
using std::list;
using std::endl;
using std::find;
using std::reverse;
using std::ifstream;

string concatenateStrings(const vector<string>& strings)
{
	string concat = "";
	for(const string& str : strings)
		concat += str;
	return concat;
}

string getSentenceOnLevel(const BinaryTree<string>& tree, size_t level)
{
	return concatenateStrings(tree.level(level));
}

bool task1(const BinaryTree<string>& tree)
{
	string sentence = getSentenceOnLevel(tree, 0);
	for (int i = 1; i < tree.height(); ++i)
		if(getSentenceOnLevel(tree, i) != sentence)
			return false;
	return true;
}

bool task2(const BinaryTree<list<int>>& tree, const char* trace1, const char* trace2)
{
	list<int> list1 = tree.get(trace1);
	list<int> list2 = tree.get(trace2);
	list2.reverse();
	return list1 == list2;
}

template <class T>
bool contains(const vector<T>& vec, const T& element)
{
	return find(vec.begin(), vec.end(), element) != vec.end());
}

template <class T>
vector<T> task4(const BinaryTree<T>& tree1, const BinaryTree<T>& tree2)
{
	vector<vector<T>> paths1 = tree1.pathsToLeaves();
	vector<vector<T>> paths2 = tree2.pathsToLeaves();

	for(vector<T>& path : paths1)
	{
		reverse(path.begin(), path.end());
		if(contains(paths2, path))
		{
			return path;
		}
	}
	return vector<T>();
}

bool task5 (const BinaryTree<string>& tree, int k, char *fname)
{
	string sentence = getSentenceOnLevel(tree, k);
	string word;
	ifstream file;
	file.open(fname);
	while(!file.eof())
	{
		file >> word;
		if(word == sentence)
		{
			return true;
		}
	}
	return false;
}


int main()
{

	return 0;
}
