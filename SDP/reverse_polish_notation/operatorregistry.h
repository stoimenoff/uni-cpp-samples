#ifndef _OPERATORREGISTRY_H_
#define _OPERATORREGISTRY_H_

#include <string>
#include <cmath>

#include "operator.h"

using std::string;

class OperatorRegistry
{
	private:
		vector<Operator> operators;
	public:
		Operator getOperatorFor(string symbol) const;

		void registerOperator(Operator operatr);

		bool hasOperatorFor(string symbol) const;

		static OperatorRegistry Default();
};

#endif