#include "configurator.h"

Position operator + (const Position& p1, const Position& p2)
{
	return Position(p1.row + p2.row, p1.column + p2.column);
}

const vector<Position> KnightConfigurator::knightMoves = {
	Position(-2, -1), Position(-2, 1), Position(-1, -2),
	Position(-1, 2), Position(1, -2), Position(1, 2),
	Position(2, -1), Position(2, 1)};

KnightConfigurator::KnightConfigurator(int knights, int boardSize)
{
	board.resize(boardSize);
	for(vector<bool>& row : board)
		row.resize(boardSize, false);

	solutionSteps.push(Step(Step::FIND_SOLUTION, knights));
	findNextConfiguration();
}

bool KnightConfigurator::isValid(Position position) const
{
	return position.row >= 0 &&
			position.column >= 0 &&
			position.row < board.size() &&
			position.column < board.size();
}

bool KnightConfigurator::hasHorse(Position position) const
{
	return isValid(position) && board[position.row][position.column];
}

bool KnightConfigurator::canPlaceHorse(Position position) const
{
	if(hasHorse(position))
		return false;
	for (Position knightMove : knightMoves)
		if(hasHorse(position + knightMove))
			return false;
	return true;
}

vector<Position> KnightConfigurator::getAllPossiblePositions() const
{
	vector<Position> possiblePositions;
	for (int row = 0; row < board.size(); ++row)
		for (int column = 0; column < board.size(); ++column)
			if (canPlaceHorse(Position(row, column)))
				possiblePositions.push_back(Position(row, column));
	return possiblePositions;
}

void KnightConfigurator::printCurrentConfiguration(ostream& out) const
{
	for(vector<bool> row : board)
	{
		for(bool hasHorse : row)
		{
			out << (hasHorse ? "H " : "- ");
		}
		out << endl;
	}
}

void KnightConfigurator::findNextConfiguration()
{
	if(solutionSteps.top().knightsToBePlaced == 0)
		solutionSteps.pop();

	while(!solutionSteps.empty() && solutionSteps.top().knightsToBePlaced != 0)
	{
		Step nextStep = solutionSteps.top();
		solutionSteps.pop();
		Position position = nextStep.position;

		if(nextStep.type == Step::PLACE_AT_POSITION)
		{
			board[position.row][position.column] = true;
		}
		else if(nextStep.type == Step::REMOVE_FROM_POSITION)
		{
			board[position.row][position.column] = false;
		}
		else
		{
			for (Position position : getAllPossiblePositions())
			{
				solutionSteps.push(
					Step(Step::REMOVE_FROM_POSITION, 1, position));
				solutionSteps.push(
					Step(Step::FIND_SOLUTION, nextStep.knightsToBePlaced - 1));
				solutionSteps.push(
					Step(Step::PLACE_AT_POSITION, 1, position));
			}
		}
	}
}

bool KnightConfigurator::hasNextConfiguration() const
{
	stack<Step> solutionStepsCopy = solutionSteps;
	while(!solutionStepsCopy.empty())
	{
		Step nextStep = solutionStepsCopy.top();
		solutionStepsCopy.pop();
		if(nextStep.type != Step::REMOVE_FROM_POSITION)
			return true;
	}
	return false;
}
