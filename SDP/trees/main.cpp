#include "tree.h"

int main()
{
	BinaryTree<int> intTree;

	intTree.add(15, "").add(12, "L").add(13, "R").add(16, "LL").add(17, "RL");

	cout <<
	intTree.map<int>([] (const int& number)
					{
						return number - 12;
					})
			.map<int>([] (const int& number)
					{
						return number + 65;
					})
			.map<char>([] (const int& number)
					{
						return char(number);
					})
			.map<int>([] (const char& symbol)
					{
						return int(symbol);
					})
			.reduce<int>([] (const int& result, const int& number)
						{
							return result + number;
						}, 0)
	<< endl;


	//predicate
	cout <<
	intTree.map<bool>([] (const int& number) {return number > 13;})
		   .reduce<int>([] (const int& result, const bool& number) {return result + number;}, 0)
	<< endl;

	return 0;
}
