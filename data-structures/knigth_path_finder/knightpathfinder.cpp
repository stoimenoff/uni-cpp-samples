#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <array>

using std::pair;
using std::vector;
using std::array;
using std::queue;
using std::find;

using std::ostream;
using std::cout;
using std::cin;
using std::endl;

#include "chess.h"
using namespace Chess;

const vector<Displacement> displacements = {
										Displacement(-2, -1),
										Displacement(-2, 1),
										Displacement(-1, -2),
										Displacement(-1, 2),
										Displacement(1, -2),
										Displacement(1, 2),
										Displacement(2, -1),
										Displacement(2, 1)};

vector<Position> positionsibleMoves(Position currentPosition)
{
	vector<Position> moves;
	for (Displacement displacement : displacements)
	{
		Position newPosition = currentPosition + displacement;
		if(isValidPosition(newPosition))
		{
			moves.push_back(newPosition);
		}
	}
	return moves;
}


int calculateDistance(Position initialPosition, Position desiredPosition)
{
	vector<Position> checked;
	queue<Position> movesQueue;
	movesQueue.push(initialPosition);
	checked.push_back(initialPosition);
	movesQueue.push(CONTROL);

	int distance = 0;
	Position currentPosition;
	while(movesQueue.size() > 0)
	{
		currentPosition = movesQueue.front();
		movesQueue.pop();

		if(currentPosition == CONTROL)
		{
			distance += 1;
			if(movesQueue.size() == 0)
				return -1;
			movesQueue.push(CONTROL);
			continue;
		}

		if(currentPosition == desiredPosition)
		{
			return distance;
		}

		for(Position position : (positionsibleMoves(currentPosition) / checked))
		{
			movesQueue.push(position);
			checked.push_back(position);
		}
	}
	return -1;
}

WayBoard markWay(const ChessBoard& board, Position initialPosition, Position desiredPosition, int distance)
{
	WayBoard wayBoard;
	init(wayBoard);
	Position currentPosition = desiredPosition;
	for (int i = 0; i <= distance; ++i)
	{
		wayBoard[BOARD_SIZE - currentPosition.second][currentPosition.first - 'A'] = distance - i + 48;
		currentPosition = board[BOARD_SIZE - currentPosition.second][currentPosition.first - 'A'];
	}
	return wayBoard;
}

WayBoard findWay(Position initialPosition, Position desiredPosition)
{
	vector<Position> checked;
	queue<Position> movesQueue;
	movesQueue.push(initialPosition);
	checked.push_back(initialPosition);
	movesQueue.push(CONTROL);

	int distance = 0;
	ChessBoard board;

	Position currentPosition;
	while(movesQueue.size() > 0)
	{
		currentPosition = movesQueue.front();
		movesQueue.pop();

		if(currentPosition == CONTROL)
		{
			distance += 1;
			if(movesQueue.size() == 0)
				return WayBoard();
			movesQueue.push(CONTROL);
			continue;
		}

		if(currentPosition == desiredPosition)
		{
			return markWay(board, initialPosition, desiredPosition, distance);
		}

		for(Position position : (positionsibleMoves(currentPosition) / checked))
		{
			movesQueue.push(position);
			board[BOARD_SIZE - position.second][position.first - 'A'] = currentPosition;
			checked.push_back(position);
		}
	}
	return WayBoard();
}

void printAllDistancesFrom(Position initialPosition)
{
	for (int j = BOARD_SIZE; j >= 1; --j)
	{
		for (int i = 0; i < BOARD_SIZE; ++i)
	 	{
	 		Position desiredPosition(char(i + 65), j);
	 		int distance = calculateDistance(initialPosition, desiredPosition);

	 		if(distance == -1)
	 			cout << "X ";
	 		else
	 			cout << distance << " ";
	 	}
	 	cout << endl;
	}
	cout << endl;
}

int main()
{
	Position initialPosition = inputPosition();
	Position desiredPosition = inputPosition();

	printAllDistancesFrom(initialPosition);

	cout << findWay(initialPosition, desiredPosition);

}
