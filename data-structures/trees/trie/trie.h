#ifndef _TRIE_H_
#define _TRIE_H_

#include <map>
#include <string>

#include "../../bucket/bucket.h"

using std::map;
using std::string;
using std::pair;


template <class T>
class Trie
{
	private:
		map<char, Trie<T>> children;
		Bucket<T> bucket;
		bool isRedundant() const;
		bool isLeaf() const;
	public:
		Trie<T>& set(const string& key, const T& value);
		bool contains(const string& key) const;
		const T& get(const string& key) const;
		Trie<T>& remove(const string& key);
};

template <class T>
Trie<T>& Trie<T>::set(const string& key, const T& value)
{
	if (key.empty())
		bucket.setData(value);
	else
		children[key.front()].set(key.substr(1), value);
	return *this;
}

template <class T>
bool Trie<T>::contains(const string& key) const
{
	if (key.empty())
		return bucket.hasData();
	if (children.find(key.front()) == children.end())
		return false;
	return children.at(key.front()).contains(key.substr(1));

}

template <class T>
const T& Trie<T>::get(const string& key) const
{
	if (key.empty())
		return bucket.getData();
	// Children will throw an exception if there is no such key!
	return children.at(key.front()).get(key.substr(1));
}

template <class T>
bool Trie<T>::isLeaf() const
{
	return children.size() == 0;
}

template <class T>
bool Trie<T>::isRedundant() const
{
	return isLeaf() && !bucket.hasData();
}

template <class T>
Trie<T>& Trie<T>::remove(const string& key)
{
	if (key.empty())
	{
		bucket.deleteData();
	}
	else
	{
		children.at(key.front()).remove(key.substr(1));
		/* Backtrack to remove nodes if they have become redundant
			after the deletion. */
		if (children.at(key.front()).isRedundant())
			children.erase(key.front());
	}
	return *this;
}

#endif
