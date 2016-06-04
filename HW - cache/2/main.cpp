#include <iostream>
#include "personalassistant.h"
using namespace std;

int main()
{
	string name;
	cout << "Enter your name:" << endl;
	getline(cin, name);
	cout << "Hello, " << name << "!" << endl;
	//PersonalAssistant kiro(name);
	PersonalAssistant* assistant = PersonalAssistant::instance(name);
	string command;

	cout << ">>";
	getline(cin, command);

	while(command != "exit")
	{
		//cout << kiro.processCommand(command) << endl;
		cout << assistant->processCommand(command) << endl;
		cout << ">>";
		getline(cin, command);
	}
	//kiro.writeChanges();
	assistant->writeChanges();
	return 0;
}