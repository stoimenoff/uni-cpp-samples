#include <iostream>
#include <limits>
#include <algorithm>

#include "../../../trees/binary/search_tree/bst.h"
#include "interval.h"

using std::cout;
using std::endl;
using std::min;
using std::max;

const double MAX_DOUBLE = std::numeric_limits<double>::max();
const double MIN_DOUBLE = std::numeric_limits<double>::min();

int main()
{
	BinarySearchTree<Interval> tree;
	tree.add(Interval(1, 3)).add(Interval(6, 10)).add(Interval(4, 6))
		.add(Interval(10, 20)).add(Interval(6, 9)).add(Interval(1, 2));

	Interval span(MAX_DOUBLE, MIN_DOUBLE);
	for(Interval interval : tree)
	{
		span.start = min(span.start, interval.start);
		span.end = max(span.end, interval.end);
	}
	cout << span << endl;

	return 0;
}
