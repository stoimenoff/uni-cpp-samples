#ifndef _GRAPH_UTILS_H_
#define _GRAPH_UTILS_H_

#include "graph.h"
#include "../bucket/bucket.h"

#include <queue>
#include <set>
#include <map>

using std::queue;
using std::set;
using std::map;

template <class ResultType, class VertexType>
class GraphBFSReducer
{
	public:
		virtual void nextVertex(const VertexType&) = 0;
		virtual void nextLayer() = 0;
		virtual ResultType getResult() = 0;
};

template <class ResultType, class T>
ResultType BFS(const Graph<T>& graph, const T& startingVertex,
			GraphBFSReducer<ResultType, T>& graphReducer)
{
	queue<Bucket<T>> vertexes;
	set<T> visited;
	vertexes.push(Bucket<T>(startingVertex));
	vertexes.push(Bucket<T>());
	visited.insert(startingVertex);

	while (vertexes.size() > 1)
	{
		if (!vertexes.front().hasData())
		{
			graphReducer.nextLayer();
			vertexes.pop();
			vertexes.push(Bucket<T>());
		}
		else
		{
			T currentVertex = vertexes.front().getData();
			vertexes.pop();
			graphReducer.nextVertex(currentVertex);
			for (const T& adjecent : graph.getAdjacent(currentVertex))
			{
				if (visited.count(adjecent) == 0)
				{
					visited.insert(adjecent);
					vertexes.push(Bucket<T>(adjecent));
				}
			}
		}
	}
	return graphReducer.getResult();
}

template <class T>
class BFSGraphReducer : public GraphBFSReducer<Graph<T>, T>
{
private:
	Graph<T> originalGraph;
	Graph<T> inducedGraph;
public:
	BFSGraphReducer(const Graph<T>& graph) : originalGraph(graph) {}
	virtual void nextVertex(const T& vertex)
	{
		if (!inducedGraph.containsVertex(vertex))
		{
			inducedGraph.addVertex(vertex);
		}
		for (const T& adjecent : originalGraph.getAdjacent(vertex))
		{
			if (!inducedGraph.containsVertex(adjecent))
			{
				inducedGraph.addVertex(adjecent);
				inducedGraph.addEdge(vertex, adjecent);
			}
		}
	}
	virtual void nextLayer() {}
	virtual Graph<T> getResult()
	{
		return inducedGraph;
	}
};

template <class T>
Graph<T> BFSInducedGraph(const Graph<T>& graph, const T& startingVertex)
{
	BFSGraphReducer<T> asdf(graph);
	return BFS<Graph<T>, T>(graph, startingVertex, asdf);
}

template <class T>
map<T, Graph<T>> allBFSInducedGraphs(const Graph<T>& graph)
{
	map<T, Graph<T>> graphs;
	for (const T& vertex : graph.getVertexes())
	{
		graphs[vertex] = BFSInducedGraph<T>(graph, vertex);
	}
	return graphs;
}

#endif
