#include "../../graph/graph.h"
#include "../../graph/graphutils.h"
#include "print.h"

#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <numeric>

using std::runtime_error;
using std::abs;
using std::count_if;
using std::iota;

/* 2 A */

template <class T>
unsigned int countParents(const Graph<T>& graph, const T& childVertex)
{
	auto parentOfChildVertex = [graph, childVertex](const T& vertex)
	{
		return graph.containsEdge(vertex, childVertex);
	};
	list<T> vertexes = graph.getVertexes();
	return count_if(vertexes.begin(), vertexes.end(), parentOfChildVertex);
}

template <class T>
unsigned int countChildren(const Graph<T>& graph, const T& parentVertex)
{
	return graph.getAdjacent(parentVertex).size();
}

template <class T>
unsigned int countNodes(const Graph<T>& graph)
{
	auto moreParentsThanChildren = [graph](const T& vertex)
	{
		return countParents(graph, vertex) > countChildren(graph, vertex);
	};
	list<T> vertexes = graph.getVertexes();
	return count_if(vertexes.begin(), vertexes.end(), moreParentsThanChildren);
}

/* 2 B */


bool existsLadderStartingWith(int start)
{
	return start >= 0 || start % 2 == 0;
}

int endOfLadderStartingWith(int start)
{
	if (existsLadderStartingWith(start))
		return (start > 0) ? start * 2 : start / 2;
	else
		throw runtime_error("Invalid ladder start!");
}

unsigned int ladderLength(int start)
{
	return abs(start - endOfLadderStartingWith(start)) + 1;
}

bool containsLadderStartingWith(const Graph<int>& graph, int vertex)
{
	if (!existsLadderStartingWith(vertex))
		return false;
	int end = endOfLadderStartingWith(vertex);
	for (int currentVertex = vertex; currentVertex < end ; ++currentVertex)
	{
		if (!graph.containsVertex(currentVertex))
			return false;
		if (!graph.containsVertex(currentVertex + 1))
			return false;
		if (!graph.containsEdge(currentVertex, currentVertex + 1))
			return false;
	}
	return true;
}

list<int> constructLadder(int start)
{
	list<int> ladder(ladderLength(start));
	iota(ladder.begin(), ladder.end(), start);
	return ladder;
}

list<int> shortestLadder(const Graph<int>& graph)
{
	// -1 is invalid ladder start, so it is safe to use as a special code
	int shortestLadderStart = -1;
	for (int vertex : graph.getVertexes())
		if (existsLadderStartingWith(vertex))
			if (shortestLadderStart == -1 || ladderLength(vertex) < ladderLength(shortestLadderStart))
				if (containsLadderStartingWith(graph, vertex))
					shortestLadderStart = vertex;
	return shortestLadderStart == -1 ? list<int>() : constructLadder(shortestLadderStart);
}

int main()
{
	Graph<int> graph = graphFromAdjacencyLists<int>({
		{0, 3}, {1, 4, 3}, {2, 1}, {3, 2}, {4, 6, 2}, {5, 2, 4, 1, 0}, {6, 5, 1}
	});
	// graph.dottyPrint(std::cerr);
	std::cout << countNodes(graph) << std::endl;

	Graph<int> ladderGraph = graphFromAdjacencyLists<int>({
		{1, 3}, {2, 3, 4}, {3, 2, 4}, {4, 1, 2}
	});
	ladderGraph.dottyPrint(std::cerr);
	std::cout << shortestLadder(ladderGraph) << std::endl;

	return 0;
}
