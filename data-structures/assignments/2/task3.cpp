#include "../../graph/graph.h"
#include "../../graph/graphutils.h"
#include "print.h"

#include <iterator>
#include <algorithm>
#include <functional>

using std::prev;
using std::all_of;
using std::bind;

template <class T>
bool isPath(const Graph<T>& graph, const list<T>& potentialPath)
{
	typename list<T>::const_iterator it = potentialPath.cbegin();
	T potentialOutVertex, potentialInVertex;

	for (; it != prev(potentialPath.cend()); ++it)
	{
		potentialOutVertex = *it;
		potentialInVertex = *(next(it));
		if (!graph.containsVertex(potentialOutVertex))
			return false;
		if (!graph.containsVertex(potentialInVertex))
			return false;
		if (!graph.containsEdge(potentialOutVertex, potentialInVertex))
			return false;
	}
	return true;
}

template <class T>
bool arePaths(const Graph<T>& graph, const list<list<T>> potentialPaths)
{
	return all_of(potentialPaths.begin(), potentialPaths.end(), bind(isPath, graph));
}

int main()
{
	Graph<int> graph = graphFromAdjacencyLists<int>({
		{0, 3}, {1, 4, 3}, {2, 1}, {3, 2}, {4, 6, 2}, {5, 2, 4, 1, 0}, {6, 5, 1}
	});

	// graph.dottyPrint(std::cerr);

	list<list<int>> paths = {{1, 3, 2}, {3, 2, 1, 4, 6, 5, 0, 3, 2, 1},
							{5, 4}, {5, 3}, {5, 11}, {11, 5}};

	for (const list<int>& path : paths)
	{
		std::cout << "Path " << path << "was ";
		std::cout << (isPath(graph, path) ? "" : "NOT ");
		std::cout << "found in the graph." << std::endl;
	}

	return 0;
}
