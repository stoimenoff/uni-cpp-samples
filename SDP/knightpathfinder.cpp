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

typedef pair<char, int> position;
typedef array<array<position, BOARD_SIZE>, BOARD_SIZE> ChessBoard;
typedef array<array<char, BOARD_SIZE>, BOARD_SIZE> WayBoard;

const position CONTROL(' ', 0);

ostream& operator<<(ostream& out, const position& pos)
{
	out << pos.first << pos.second;
	return out;
}

ostream& operator<<(ostream& out, const ChessBoard& board)
{
	for (array<position, BOARD_SIZE> row : board)
	{
		for (position &pos : row)
		{
			out << pos << " ";
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

bool operator==(const position& pos1, const position& pos2)
{
	return pos1.first == pos2.first && pos1.second == pos2.second;
}

position operator+(const position& pos, const pair<int, int>& margin)
{
	return position(pos.first + margin.first, pos.second + margin.second);
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

bool isValidPosition(position pos)
{
	char letter = pos.first;
	int number = pos.second;
	if(letter < 'A' || letter > 'A' + BOARD_SIZE - 1)
		return false;
	if(number < 1 || number > BOARD_SIZE)
		return false;
	return true;
}

const vector<pair<int, int>> margins = {pair<int, int>(-2, -1),
										pair<int, int>(-2, 1),
										pair<int, int>(-1, -2),
										pair<int, int>(-1, 2),
										pair<int, int>(1, -2),
										pair<int, int>(1, 2),
										pair<int, int>(2, -1),
										pair<int, int>(2, 1)};

vector<position> possibleMoves(position currentPosition)
{
	vector<position> moves;
	for (pair<int, int> margin : margins)
	{
		position newPosition = currentPosition + margin;
		if(isValidPosition(newPosition))
		{
			moves.push_back(newPosition);
		}
	}
	return moves;
}

//vector set difference
vector<position> operator/(vector<position> v1, vector<position> v2)
{
	vector<position> difference;
	for(position& pos : v1)
	{
		if(find(v2.begin(), v2.end(), pos) == v2.end())
			difference.push_back(pos);
	}
	return difference;
}

position inputPosition()
{
	char initialLetter;
	int initialNumber;
	cin >> initialLetter >> initialNumber;
	return position(initialLetter, initialNumber);
}

int calculateDistance(position initialPosition, position desiredPosition)
{
	vector<position> checked;
	queue<position> movesQueue;
	movesQueue.push(initialPosition);
	checked.push_back(initialPosition);
	movesQueue.push(CONTROL);

	int distance = 0;
	position currentPosition;
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

		for(position pos : (possibleMoves(currentPosition) / checked))
		{
			movesQueue.push(pos);
			checked.push_back(pos);
		}
	}
	return -1;
}

WayBoard markWay(const ChessBoard& board, position initialPosition, position desiredPosition, int distance)
{
	WayBoard wayBoard;
	init(wayBoard);
	position currentPosition = desiredPosition;
	for (int i = 0; i <= distance; ++i)
	{
		wayBoard[BOARD_SIZE - currentPosition.second][currentPosition.first - 'A'] = distance - i + 48;
		currentPosition = board[BOARD_SIZE - currentPosition.second][currentPosition.first - 'A'];
	}
	return wayBoard;
}

WayBoard findWay(position initialPosition, position desiredPosition)
{
	vector<position> checked;
	queue<position> movesQueue;
	movesQueue.push(initialPosition);
	checked.push_back(initialPosition);
	movesQueue.push(CONTROL);

	int distance = 0;
	ChessBoard board;

	position currentPosition;
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

		for(position pos : (possibleMoves(currentPosition) / checked))
		{
			movesQueue.push(pos);
			board[BOARD_SIZE - pos.second][pos.first - 'A'] = currentPosition;
			checked.push_back(pos);
		}
	}
	return WayBoard();
}

void printAllDistancesFrom(position initialPosition)
{
	for (int j = BOARD_SIZE; j >= 1; --j)
	{
		for (int i = 0; i < BOARD_SIZE; ++i)
	 	{
	 		position desiredPosition(char(i + 65), j);
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
	position initialPosition = inputPosition();
	position desiredPosition = inputPosition();

	printAllDistancesFrom(initialPosition);

	cout << findWay(initialPosition, desiredPosition);

}