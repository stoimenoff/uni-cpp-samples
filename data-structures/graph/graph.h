#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "idgenerator.h"

#include <map>
#include <unordered_set>
#include <list>
#include <vector>
#include <ostream>

using std::map;
using std::unordered_set;
using std::list;
using std::vector;
using std::ostream;
using std::endl;

template <class T>
class Graph
{
	private:
		struct Vertex
		{
			T data;
			unordered_set<size_t> adjacentIDs;
			Vertex() {}
			Vertex(const T& data) : data(data) {}
		};
		IDGenerator idGenerator;
		map<T, size_t> ids;
		map<size_t, Vertex> vertexes;
	public:
		void addVertex(const T& vertexData);
		void addEdge(const T& firstVertexData, const T& secondVertexData);
		void deleteVertex(const T& vertexData);
		void deleteEdge(const T& firstVertexData, const T& secondVertexData);
		void dottyPrint(ostream& out) const;
		list<T> getAdjacent(const T& vertexData) const;
};

template <class T>
void Graph<T>::addVertex(const T& vertexData)
{
	size_t id = idGenerator.getID();
	ids[vertexData] = id;
	vertexes[id] = Vertex(vertexData);
}

template <class T>
void Graph<T>::deleteVertex(const T& vertexData)
{
	size_t id = ids.erase(vertexData);
	vertexes.erase(id);
	idGenerator.free(id);
	for (auto& entry : vertexes)
	{
		entry.second.adjacentIDs.erase(id);
	}
}

template <class T>
void Graph<T>::addEdge(const T& firstVertexData, const T& secondVertexData)
{
	size_t firstID = ids.at(firstVertexData);
	size_t secondID = ids.at(secondVertexData);
	vertexes.at(firstID).adjacentIDs.insert(secondID);
}

template <class T>
void Graph<T>::deleteEdge(const T& firstVertexData, const T& secondVertexData)
{
	size_t firstID = ids.at(firstVertexData);
	size_t secondID = ids.at(secondVertexData);
	vertexes.at(firstID).adjacentIDs.erase(secondID);
}

template <class T>
void Graph<T>::dottyPrint(ostream& out) const
{
	out << "digraph G\n{" << endl;
	for (const auto& entry : ids)
		out << entry.second << "[label=\"" << entry.first << "\"];" << endl;
	for (const auto& entry : vertexes)
		for (const size_t& adjID : entry.second.adjacentIDs)
			out << entry.first << " -> " << adjID << ";" << endl;
	out << "}" << endl;
}

template <class T>
list<T> Graph<T>::getAdjacent(const T& vertexData) const
{
	list<T> adjacent;
	for (size_t id : vertexes.at(ids.at(vertexData)).adjacentIDs)
		adjacent.push_back(vertexes.at(id).data);
	return adjacent;
}

#endif
