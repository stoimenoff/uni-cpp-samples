#ifndef _KNIGHT_CONFIGURATOR_H_
#define _KNIGHT_CONFIGURATOR_H_

#include <vector>
#include <stack>
#include <ostream>

using std::vector;
using std::stack;
using std::pair;
using std::ostream;
using std::endl;

struct Position
{
	int row;
	int column;
	Position(int row, int column) : row(row), column(column) {}
};

struct Step
{
	static const int PLACE_AT_POSITION = 0;
	static const int REMOVE_FROM_POSITION = 1;
	static const int FIND_SOLUTION = 2;

	int type;
	int knightsToBePlaced;
	Position position;
	Step(int type, int knightsToBePlaced, Position position = Position(-1, -1))
		: type(type), knightsToBePlaced(knightsToBePlaced),
			position(position) {}
};

Position operator + (const Position& p1, const Position& p2);

class KnightConfigurator
{
	public:
		KnightConfigurator(int knights, int boardSize = 8);
		void printCurrentConfiguration(ostream& out) const;
		bool hasNextConfiguration() const;
		void findNextConfiguration();
	private:
		static const vector<Position> knightMoves;

		bool isValid(Position position) const;
		bool hasHorse(Position position) const;
		bool canPlaceHorse(Position position) const;
		vector<Position> getAllPossiblePositions() const;

		vector<vector<bool>> board;
		stack<Step> solutionSteps;
};

#endif
