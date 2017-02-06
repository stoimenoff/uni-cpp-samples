#include "plant.h"

#include <iostream>
#include <queue>
#include <list>
#include <cmath>

using namespace std;

// Return pair of sum of positives and sum of negatives
pair<double, double> sums(queue<double> numbers)
{
	pair<double, double> sums(0, 0);
	while (!numbers.empty())
	{
		if (numbers.front() > 0)
			sums.first += numbers.front();
		if (numbers.front() < 0)
			sums.second += numbers.front();
		numbers.pop();
	}
	return sums;
}

list<pair<double, double>> mapToPairsOfSums(list<queue<double>> queues)
{
	list<pair<double, double>> listOfSumPairs;
	for (const queue<double>& currentQueue : queues)
		listOfSumPairs.push_back(sums(currentQueue));
	return listOfSumPairs;
}

double sumSeconds(list<pair<double, double>> pairs)
{
	double sum = 0;
	for (const pair<double, double>& currentPair : pairs)
		sum += currentPair.second;
	return sum;
}

void findSplit(const list<queue<double>>& queues)
{
	list<pair<double, double>> sums = mapToPairsOfSums(queues);
	double negativesSum = sumSeconds(sums);
	double positivesSum = 0;
	for (const pair<double, double>& currentSumsPair : sums)
	{
		positivesSum += currentSumsPair.first;
		negativesSum -= currentSumsPair.second;
		if (positivesSum == fabs(negativesSum))
		{
			cout << positivesSum << endl;
			return;
		}
	}
}

//Examples

queue<double> queueFromList(list<double> numbers)
{
	queue<double> numbersQueue;
	for (double number : numbers)
		numbersQueue.push(number);
	return numbersQueue;
}

int main()
{
	list<queue<double>> queues;

	queues.push_back(queueFromList({5, -7}));
	queues.push_back(queueFromList({10, -3, -7}));
	queues.push_back(queueFromList({7}));
	queues.push_back(queueFromList({-6, 3}));
	queues.push_back(queueFromList({-8, -1, 9}));

	/*
			5  10  7  -6  -8
			|   |      |   |
		   -7  -3      3  -1
		        |          |
			   -7          9
		Split after the second one. Sum = 15
	*/

	findSplit(queues);

	return 0;
}
