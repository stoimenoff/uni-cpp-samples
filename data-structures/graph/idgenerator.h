#ifndef _IDGEN_H_
#define _IDGEN_H_

#include <queue>
using std::queue;
using std::size_t;

class IDGenerator
{
	private:
		queue<size_t> freed;
		size_t currentID = 0;
	public:
		size_t getID();
		void free(const size_t& freedID);
};

#endif
