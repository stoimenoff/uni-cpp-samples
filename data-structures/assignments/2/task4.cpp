#include "../../graph/graph.h"
#include "../../graph/graphutils.h"
#include "print.h"

#include <set>

using std::set;

template <class T>
bool containsCycle(const list<T>& path)
{
	return set<T>(path.begin(), path.end()).size() < path.size();
}

template <class T>
bool doesNotContainCycle(const list<T>& path)
{
	return !containsCycle(path);
}

template <class T>
list<list<T>> allAcyclicPaths(const Graph<T>& graph, const T& start, const T& end)
{
	list<list<T>> result;
	list<list<T>> paths = {{start}};

	while (!paths.empty())
	{
		list<T> path = paths.front();
		paths.pop_front();
		if (path.back() == end)
		{
			result.push_back(path);
		}
		else if (doesNotContainCycle(path))
		{
			for (const T& vertex : graph.getAdjacent(path.back()))
			{
				path.push_back(vertex);
				paths.push_back(path);
				path.pop_back();
			}
		}
	}
	return result;
}

template <class T>
bool vertexSubset(const list<T>& firstPath, const list<T>& secondPath)
{
	set<T> firstSet(firstPath.cbegin(), firstPath.cend());
	for (const T& vertex : secondPath)
		if (firstSet.count(vertex) == 0)
			return false;
	return true;

}

template <class T>
list<T> findReversablePath(const Graph<T>& graph, const T& start, const T& end)
{
	list<list<T>> reversePaths = allAcyclicPaths(graph, end, start);
	for (const list<int>& path : allAcyclicPaths(graph, start, end))
		for (const list<int>& reversePath : reversePaths)
			if (vertexSubset(path, reversePath))
				return path;
	return {};
}

int main()
{
	Graph<int> graph = graphFromAdjacencyLists<int>({
		{0, 3}, {1, 4, 3}, {2, 1}, {3, 2}, {4, 6, 2}, {5, 2, 4, 1, 0}, {6, 5, 1}
	});

	// graph.dottyPrint(std::cerr);

	for (int a = 0; a < 7; ++a)
	{
		for (int b = 0; b < 7; ++b)
		{
			std::cout << "All acyclic paths from: " << a << " to " << b << endl;
			for (const list<int>& path : allAcyclicPaths(graph, a, b))
				std::cout << path << std::endl;
			std::cout << std::endl;
		}
	}

	return 0;
}
