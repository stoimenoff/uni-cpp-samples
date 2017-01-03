#include "idgenerator.h"

size_t IDGenerator::getID()
{
	size_t id;
	if (freed.empty())
	{
		id = currentID;
		currentID++;
	}
	else
	{
		id = freed.front();
		freed.pop();
	}
	return id;

}

void IDGenerator::free(const size_t& freedID)
{
	freed.push(freedID);
}
