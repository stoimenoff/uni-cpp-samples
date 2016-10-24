#include "expressionparser.h"
#include <iostream>

struct Node
{
	string value;
	Node *left;
	Node *right;

	Node(string value, Node *left = NULL, Node *right = NULL)
		: value(value), left(left), right(right) {}

	~Node() {delete left; delete right;}
};

Node* nodeFromStack(stack<string>& tokens, const OperatorRegistry& operatorsRegistry)
{
	string token = tokens.top();
	tokens.pop();
	if(!operatorsRegistry.hasOperatorFor(token))
	{
		return new Node(token, NULL, NULL);
	}
	return new Node(token, nodeFromStack(tokens, operatorsRegistry), nodeFromStack(tokens, operatorsRegistry));
}

void dottyPrint(Node* node, int id)
{
	if(node == NULL)
		return;
	std::cout << id << "[label=\"" << node->value << "\"];" << std::endl;
	if(node->left != NULL)
		std::cout << id << " -> " << 2*id + 1 << ";" << std::endl;
	if(node->right != NULL)
		std::cout << id << " -> " << 2*id + 2 << ";" << std::endl;
	dottyPrint(node->right, 2*id + 1);
	dottyPrint(node->left, 2*id + 2);

}

void dottyPrint(Node* node)
{
	std::cout << "digraph G{" << std::endl;
	dottyPrint(node, 0);
	std::cout << "}" << std::endl;
}

stack<string> queueToStack(queue<string> tokensQueue)
{
	stack<string> tokens;
	while(!tokensQueue.empty())
	{
		tokens.push(tokensQueue.front());
		tokensQueue.pop();
	}
	return tokens;
}

int main()
{
	string input;
	std::getline(std::cin, input);

	ExpressionParser parser;

	stack<string> tokens = queueToStack(parser.getReversedPolishNotationOf(input));

	dottyPrint(nodeFromStack(tokens, parser.getOperatorsRegistry()));

	return 0;
}

