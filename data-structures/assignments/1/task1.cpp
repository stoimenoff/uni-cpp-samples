#include "plant.h"

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <cmath>

using namespace std;

stack<Plant> readStackFromTextFile(const string& filename)
{
	ifstream plantsInput(filename);
	stack<Plant> plants;
	Plant plant;

	while (plantsInput >> plant)
		plants.push(plant);

	return plants;
}

template<typename T>
list<T> stackToList(stack<T> items)
{
	list<T> listItems;
	while (!items.empty())
	{
		listItems.push_front(items.top());
		items.pop();
	}
	return listItems;
}

queue<stack<Plant>> dispatch(stack<Plant> plantsStack, stack<double> temperatures)
{
	list<Plant> plants = stackToList(plantsStack);
	queue<stack<Plant>> dispatched;

	Plant plant;
	stack<Plant> currentStack;
	while (!temperatures.empty())
	{
		currentStack = stack<Plant>();
		double temperature = temperatures.top();
		temperatures.pop();

		list<Plant>::iterator it = plants.begin();
		while (it != plants.end())
		{
			plant = *it;
			if (plant.minTemperature <= temperature && plant.maxTemperature >= temperature)
			{
				currentStack.push(plant);
				it = plants.erase(it);
			}
			else
			{
				++it;
			}
		}

		dispatched.push(currentStack);
	}

	return dispatched;
}

void writeListToBinary(list<Plant> plants, const string& filename)
{
	ofstream out(filename, ios::binary);
	for (const Plant& plant : plants)
		writeToBinary(out, plant);
}

list<Plant> filterPlants(list<Plant> plants, double temperature)
{
	plants.remove_if([temperature] (const Plant& plant)
		{
			return fabs(plant.averageTemperature() - temperature) > 2;
		});
	return plants;
}

void writeFilteredToFile(stack<Plant> plantsStack, double temperature)
{
	const string filename = "botanic.bin";
	list<Plant> plants = stackToList(plantsStack);
	plants = filterPlants(plants, temperature);
	writeListToBinary(plants, filename);
}

int main()
{

	//Examples

	stack<Plant> plants = readStackFromTextFile("plants.txt");
	stack<double> temperatures;
	temperatures.push(18);
	temperatures.push(25);
	temperatures.push(10);

	queue<stack<Plant>> dispatched = dispatch(plants, temperatures);
	while (!dispatched.empty())
	{
		stack<Plant> currentStack = dispatched.front();
		cout << "START OF STACK" << endl;
		while (!currentStack.empty())
		{
			cout << currentStack.top() << endl;
			currentStack.pop();
		}
		cout << "END OF STACK" << endl;
		dispatched.pop();
	}

	writeFilteredToFile(plants, 25);

	ifstream in("botanic.bin", ios::binary);
	Plant plant;
	while (readFromBinary(in, plant))
	{
		cout << plant << endl;
	}

	// while (!plants.empty())
	// {
	// 	cout << plants.top() << endl;
	// 	plants.pop();
	// }

	return 0;
}
