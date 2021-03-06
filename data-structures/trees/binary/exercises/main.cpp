#include "tree.h"
#include <iomanip>

using std::boolalpha;

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

	for(auto& element : intTree.listLeaves())
	{
		cout << element << endl;
	}

	cout << intTree.findTrace(17) << endl;
	cout << intTree.findTrace(16) << endl;
	cout << intTree.findTrace(18) << endl;

	intTree.prettyPrint();
	intTree.simplePrint();
	intTree.dottyPrint(cout);

	for (int i = 0; i < 4; ++i)
	{
		cout << "Level " << i << "----------" << endl;
		for(auto& element : intTree.level(i))
		{
			cout << element << endl;
		}
		cout << "-----------------" << endl;
	}

	for (int i = 0; i < 5; ++i)
	{
		intTree[i] += 1;
	}
	intTree.prettyPrint();

	cout << intTree.isBST() << endl;

	BinaryTree<int> bst;

	bst.add(15, "").add(12, "L").add(18, "R").add(11, "LL").add(17, "RL");

	cout << boolalpha;
	cout << bst.isBST() << endl;
	cout << bst.isSymetrical() << endl;

	BinaryTree<int> symetricTree;
	symetricTree.add(15, "").add(12, "L").add(12, "R").add(11, "LL").add(11, "RR");
	cout << symetricTree.isSymetrical() << endl;


	for(auto path : intTree.pathsToLeaves())
	{
		for(auto element : path)
		{
			cout << element << " ";
		}
		cout << endl;
	}

	return 0;
}
