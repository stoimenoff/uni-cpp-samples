#include <iostream>

#include "trie.h"

using std::cout;
using std::endl;

void testBasicsTrie()
{
	Trie<int> map;
	map.set("babati", 1);
	map.set("babati2", 2);
	map.set("babati3", 3);
	map.set("babati2dyadoti", 4);
	map.set("babati2dyadoti", 5);

	cout << map.get("babati2dyadoti") << endl;

	assert(map.contains("babati2dyadoti"));
	assert(map.contains("babati"));
	assert(map.contains("babati2"));
	assert(!map.contains("baba"));
	assert(!map.contains(""));

	map.remove("babati");
	map.remove("babati2dyadoti");

	assert(!map.contains("babati"));
	assert(!map.contains("babati2dyadoti"));

}

int main()
{
	testBasicsTrie();

	return 0;
}
