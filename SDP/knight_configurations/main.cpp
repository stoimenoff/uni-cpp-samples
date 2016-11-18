#include <iostream>

using std::cout;
using std::endl;

#include "configurator.h"

int main()
{
	KnightConfigurator configurator(4, 3);
	while(configurator.hasNextConfiguration())
	{
		cout << "+++++++++++++++++++++++" << endl;
		configurator.printCurrentConfiguration(cout);
		cout << "+++++++++++++++++++++++" << endl;
		configurator.findNextConfiguration();
	}
	return 0;
}
