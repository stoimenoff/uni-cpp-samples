#ifndef _GRAPH_UTILS_H_
#define _GRAPH_UTILS_H_

#include "graph.h"
#include "../bucket/bucket.h"

#include <queue>
#include <set>
#include <map>
#include <vector>

using std::queue;
using std::set;
using std::map;
using std::vector;

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
	vertexes.push(Bucket<T>());
	vertexes.push(Bucket<T>(startingVertex));
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
	BFSGraphReducer<T> BFSGraphInducer(graph);
	return BFS<Graph<T>, T>(graph, startingVertex, BFSGraphInducer);
}

template <class T>
class BFSGraphLayerReducer : public GraphBFSReducer<vector<set<T>>, T>
{
private:
	Graph<T> originalGraph;
	vector<set<T>> layers;
public:
	virtual void nextVertex(const T& vertex)
	{
		layers.back().insert(vertex);
	}
	virtual void nextLayer()
	{
		layers.push_back(set<T>());
	}
	virtual vector<set<T>> getResult()
	{
		return layers;
	}
};

template <class T>
vector<set<T>> BFSInducedLayers(const Graph<T>& graph, const T& startingVertex)
{
	BFSGraphLayerReducer<T> layerReducer;
	return BFS<vector<set<T>>, T>(graph, startingVertex, layerReducer);
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
