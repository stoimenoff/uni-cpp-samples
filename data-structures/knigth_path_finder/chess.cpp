#include "chess.h"

using namespace Chess;

ostream& Chess::operator<<(ostream& out, const Position& position)
{
	out << position.first << position.second;
	return out;
}

ostream& Chess::operator<<(ostream& out, const ChessBoard& board)
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

ostream& Chess::operator<<(ostream& out, const WayBoard& board)
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

bool Chess::operator==(const Position& position1, const Position& position2)
{
	return position1.first == position2.first && position1.second == position2.second;
}

Position Chess::operator+(const Position& position, const Displacement& displacement)
{
	return Position(position.first + displacement.first, position.second + displacement.second);
}

bool Chess::isValidPosition(Position position)
{
	char letter = position.first;
	int number = position.second;
	if(letter < 'A' || letter > 'A' + BOARD_SIZE - 1)
		return false;
	if(number < 1 || number > BOARD_SIZE)
		return false;
	return true;
}

//vector set difference
vector<Position> Chess::operator/(vector<Position> v1, vector<Position> v2)
{
	vector<Position> difference;
	for(Position& position : v1)
	{
		if(find(v2.begin(), v2.end(), position) == v2.end())
			difference.push_back(position);
	}
	return difference;
}

Position Chess::inputPosition()
{
	char initialLetter;
	int initialNumber;
	cin >> initialLetter >> initialNumber;
	return Position(initialLetter, initialNumber);
}

void Chess::init(WayBoard& wayBoard)
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			wayBoard[i][j] = '-';
		}
	}
}
