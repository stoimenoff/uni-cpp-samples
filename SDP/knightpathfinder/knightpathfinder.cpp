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

const int BOARD_SIZE = 8;

typedef pair<char, int> Position;
typedef pair<int, int> Displacement;
typedef array<array<Position, BOARD_SIZE>, BOARD_SIZE> ChessBoard;
typedef array<array<char, BOARD_SIZE>, BOARD_SIZE> WayBoard;

const Position CONTROL(' ', 0);

ostream& operator<<(ostream& out, const Position& position)
{
	out << position.first << position.second;
	return out;
}

ostream& operator<<(ostream& out, const ChessBoard& board)
{
	for (array<Position, BOARD_SIZE> row : board)
	{
		for (Position &position : row)
		{
			out << position << " ";
		}
		out << endl;
	}
	return out;
}

ostream& operator<<(ostream& out, const WayBoard& board)
{
	for (array<char, BOARD_SIZE> row : board)
	{
		for (char &c : row)
		{
			out << c << " ";
		}
		out << endl;
	}
	return out;
}

bool operator==(const Position& position1, const Position& position2)
{
	return position1.first == position2.first && position1.second == position2.second;
}

Position operator+(const Position& position, const Displacement& displacement)
{
	return Position(position.first + displacement.first, position.second + displacement.second);
}

void init(WayBoard& wayBoard)
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			wayBoard[i][j] = '-';
		}
	}
}

bool isValidPosition(Position position)
{
	char letter = position.first;
	int number = position.second;
	if(letter < 'A' || letter > 'A' + BOARD_SIZE - 1)
		return false;
	if(number < 1 || number > BOARD_SIZE)
		return false;
	return true;
}

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

//vector set difference
vector<Position> operator/(vector<Position> v1, vector<Position> v2)
{
	vector<Position> difference;
	for(Position& position : v1)
	{
		if(find(v2.begin(), v2.end(), position) == v2.end())
			difference.push_back(position);
	}
	return difference;
}

Position inputPosition()
{
	char initialLetter;
	int initialNumber;
	cin >> initialLetter >> initialNumber;
	return Position(initialLetter, initialNumber);
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
