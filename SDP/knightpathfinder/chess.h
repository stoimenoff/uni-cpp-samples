#ifndef _CHESS_H_
#define _CHESS_H_

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
using std::cin;
using std::endl;

namespace Chess
{

	const int BOARD_SIZE = 8;

	typedef pair<char, int> Position;
	typedef pair<int, int> Displacement;
	typedef array<array<Position, BOARD_SIZE>, BOARD_SIZE> ChessBoard;
	typedef array<array<char, BOARD_SIZE>, BOARD_SIZE> WayBoard;

	const Position CONTROL(' ', 0);

	ostream& operator<<(ostream& out, const Position& position);

	ostream& operator<<(ostream& out, const ChessBoard& board);

	ostream& operator<<(ostream& out, const WayBoard& board);

	bool operator==(const Position& position1, const Position& position2);

	Position operator+(const Position& position, const Displacement& displacement);

	bool isValidPosition(Position position);

	//vector set difference
	vector<Position> operator/(vector<Position> v1, vector<Position> v2);

	Position inputPosition();

	void init(WayBoard& wayBoard);

} /* Chess */

#endif
