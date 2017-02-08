#include "../../graph/graph.h"
#include "../../graph/graphutils.h"
#include "print.h"

#include <set>
#include <iterator>

using std::set;
using std::prev;

template <class T>
bool singleChild(Graph<T>& graph, const T& childVertex)
{
	for (const T& vertex : graph.getVertexes())
		if (graph.containsEdge(vertex, childVertex))
			if (graph.getAdjacent(vertex).size() > 1)
				return false;
	return true;
}

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
bool isLasso(const list<T>& path)
{
	if (doesNotContainCycle(path))
		return false;
	if (containsCycle(list<T>(path.begin(), prev(path.end()))))
		return false;
	return true;
}

template <class T>
list<list<T>> allLassos(const Graph<T>& graph)
{
	list<list<T>> lassos;
	list<list<T>> paths;
	for (const T& vertex : graph.getVertexes())
		paths.push_back({vertex});

	while (!paths.empty())
	{
		list<T> path = paths.front();
		paths.pop_front();
		if (isLasso(path))
		{
			lassos.push_back(path);
		}
		else
		{
			for (const T& vertex : graph.getAdjacent(path.back()))
			{
				path.push_back(vertex);
				paths.push_back(path);
				path.pop_back();
			}
		}
	}
	return lassos;
}

template <class T>
list<T> longestLasso(const Graph<T>& graph)
{
	list<T> longest;
	for (const list<T>& lasso : allLassos(graph))
		if (lasso.size() > longest.size())
			longest = lasso;
	return longest;
}

int main()
{
	Graph<int> graph = graphFromAdjacencyLists<int>({
		{0, 3}, {1, 4, 3}, {2, 1}, {3, 2}, {4, 6, 2},
		{5, 2, 4, 1, 0}, {6, 5, 1}, {3, 7}, {7, 8}
	});

	std::cout << "Lassos:" << std::endl;
	for (const list<int>& lasso : allLassos(graph))
		std::cout << lasso << std::endl;

	std::cout << "Longest: " << longestLasso(graph) << std::endl << std::endl;

	// graph.dottyPrint(std::cerr);

	for (int i = 0; i < 9; ++i)
	{
		std::cout << std::boolalpha << "Signle child? " << i << ": ";
		std::cout << singleChild(graph, i) << std::endl;
	}

	return 0;
}
