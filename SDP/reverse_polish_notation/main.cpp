#include "expressionparser.h"
#include <iostream>

struct Node
{
	string value;
	Node *left;
	Node *right;

	Node(string value, Node *left = nullptr, Node *right = nullptr)
		: value(value), left(left), right(right) {}

	~Node() {delete left; delete right;}
};

Node* nodeFromStack(stack<string>& tokens, const OperatorRegistry& operatorsRegistry)
{
	string token = tokens.top();
	tokens.pop();
	int children = 0;
	Node *leftChild = nullptr, *rightChild = nullptr;
	if(operatorsRegistry.hasOperatorFor(token))
	{
		children = operatorsRegistry.getOperatorFor(token).getArgumentsCount();
	}
	if(children > 0)
	{
		rightChild = nodeFromStack(tokens, operatorsRegistry);
	}
	if(children > 1)
	{
		leftChild = nodeFromStack(tokens, operatorsRegistry);
	}
	return new Node(token, leftChild, rightChild);
}

void dottyPrint(Node* node, int id)
{
	if(node == nullptr)
		return;
	std::cout << id << "[label=\"" << node->value << "\"];" << std::endl;
	if(node->left != nullptr)
		std::cout << id << " -> " << 2*id + 1 << ";" << std::endl;
	if(node->right != nullptr)
		std::cout << id << " -> " << 2*id + 2 << ";" << std::endl;
	dottyPrint(node->right, 2*id + 2);
	dottyPrint(node->left, 2*id + 1);

}

void dottyPrint(Node* node)
{
	std::cout << "digraph G{" << std::endl;
	dottyPrint(node, 0);
	std::cout << "}" << std::endl;
}

int main()
{
	string input;
	std::getline(std::cin, input);

	ExpressionParser parser;

	stack<string> tokens = parser.getStackReversedPolishNotationOf(input);

	dottyPrint(nodeFromStack(tokens, parser.getOperatorsRegistry()));

	return 0;
}
