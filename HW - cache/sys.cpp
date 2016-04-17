#include "dispatcher.h"

using namespace std;

int main()
{
	//Create the system and start it
	Dispatcher system;
	system.start();

	//Register section, registration is optional
	int choice = -1;
	cout << "Do you want to register ?" << endl;
	cout << "1: Yes" << endl;
	cout << "2: No" << endl;
	cin >> choice;
	while(choice < 1 || choice > 2)
	{
		cout << "Invalid choice, please choose again!" << endl;
		cin >> choice;
	}
	cin.get();
	if (choice == 1)
		system.registerUser();

	//Login - if it is unsuccessful skip the functionality and shutdown
	if (system.login())
	{
		do
		{
			cout << "What do you want to do?" << endl;
			cout << "1: Display/Sort movies" << endl;
			cout << "2: Search/Filter movies" << endl;
			cout << "3: Rate/Review a movie" << endl;
			cout << "4: Search for a movie remakes" << endl;
			cout << "5: Read movie reviews" << endl;
			if (system.loggedAdmin())
			{
				cout << "6: Add a movie" << endl;
			}
			cout << "0: Nothing! I want to leave!" << endl;
			cin >> choice;
			while(choice < 0 || choice > 6 || (!system.loggedAdmin() && choice == 6))
			{	
				cout << "Invalid choice, please choose again!" << endl;
				cin >> choice;
			}
			switch (choice)
			{
				case 1:
					system.sortMovies();
					break;
				case 2:
					system.filterMovies();
					break;
				case 3:
					system.review();
					break;
				case 4:
					system.searchRemakes();
					break;
				case 5:
					system.searchReviews();
					break;
				case 6:
					system.addMovie();
					break;
			}
		}
		while(choice != 0);
	}

	//shutdown
	system.shutdown();
	return 0;
}