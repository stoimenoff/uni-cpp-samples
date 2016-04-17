#include "dispatcher.h"

//File names
const char* usersfile = "users";
const char* moviesfile = "movies";
const char* stafffile = "staff";

using std::cout;
using std::cin;
using std::endl;

/*File read and write functions*/
void Dispatcher::readUsers()
{
	int size;
	std::ifstream file(usersfile, std::ios::in);
	file >> size;
	for (int i = 0; i < size; ++i)
	{
		users.pushBack(User(file));
	}
	file.close();
}
void Dispatcher::readMovies()
{
	int size;
	std::ifstream file(moviesfile, std::ios::in);
	file >> size;
	for (int i = 0; i < size; ++i)
	{
		movies.pushBack(Movie(file));
	}
	file.close();
}
void Dispatcher::readStaff()
{
	int size;
	std::ifstream file(stafffile, std::ios::in);
	file >> size;
	for (int i = 0; i < size; ++i)
	{
		staff.pushBack(MovieStaff(file));
	}
	file.close();
}

void Dispatcher::writeUsers()
{
	std::ofstream file(usersfile, std::ios::out);
	file << users.Size();
	for (int i = 0; i < users.Size(); ++i)
	{
		users[i].writeToFileStream(file);
	}
	file.close();
}
void Dispatcher::writeMovies()
{
	std::ofstream file(moviesfile, std::ios::out);
	file << movies.Size();
	for (int i = 0; i < movies.Size(); ++i)
	{
		movies[i].writeToFileStream(file);
	}
	file.close();
}
void Dispatcher::writeStaff()
{
	std::ofstream file(stafffile, std::ios::out);
	file << staff.Size();
	for (int i = 0; i < staff.Size(); ++i)
	{
		staff[i].writeToFileStream(file);
	}
	file.close();
}
/* END OF File read and write functions*/

void Dispatcher::updateLoggedUser()
{
	if (thereIsUser())
	{
		users[getUserIndex(loggedUser.getUsername())] = loggedUser;
	}
}

/*Internal search functions, returning index*/
int Dispatcher::getUserIndex(const String &username)
{
	for (int i = 0; i < users.Size(); ++i)
	{
		if (users[i].getUsername() == username)
		{
			return i;
		}
	}
	return -1;
}

int Dispatcher::getMovieIndex(const String &movieId)
{
	for (int i = 0; i < movies.Size(); ++i)
	{
		if (movies[i].getId() == movieId)
		{
			return i;
		}
	}
	return -1;
}
/* Return the index of the nth non-remake movie in the vector
 * n = userIndex
*/
int Dispatcher::countIgnoringRemakes(int userIndex)
{
	if (userIndex < 1)
		return -1;
	int nonRemakes = 0;
	for (int i = 0; i < movies.Size(); ++i)
	{
		if (movies[i].isNotRemake())
		{
			nonRemakes += 1;
		}
		if (nonRemakes == userIndex)
		{
			return i;
		}
	}
}
/*END OF Internal search functions, returning index*/

/*Movie printing functions*/
void Dispatcher::printMovies()
{
	mapVector(movies, printMovie);
}

//Print the movies numbered from 1. Option to skip remakes.
void Dispatcher::printMoviesWithIndex(bool withoutRemakes)
{
	int index = 1;
	for (int i = 0; i < movies.Size(); ++i)
	{
		if (withoutRemakes && movies[i].isRemake())
		{
			continue;
		}
		cout << index << ": " << movies[i].getTitle();
		cout << " from " << movies[i].getYear() << endl;
		index += 1;
	}
}

void Dispatcher::printRemakesOf(const String &movieId)
{
	for (int i = 0; i < movies.Size(); ++i)
	{
		if (movies[i].getRemakeOf() == movieId)
			cout << movies[i] << endl;
	}
}

void Dispatcher::printReviewsOf(const String &movieId)
{
	for (int i = 0; i < users.Size(); ++i)
	{
		if (users[i].hasReviewed(movieId))
		{
			cout << "---------------Review--------------" << endl;
			cout << "Film: " << movies[getMovieIndex(movieId)].getTitle();
			cout << " from " << movies[getMovieIndex(movieId)].getYear() << endl;
			cout << "User: " << users[i].getUsername() << endl;
			double rating = users[i].getRatingFor(movieId);
			String comment = users[i].getReviewFor(movieId);
			if (rating != 0)
				cout << "Rating: " << rating << endl;
			if (comment != "")
				cout << "Comment: " << comment << endl;
		}
	}
}
/*END OF Movie printing functions*/



/*Staff related internal functionalities*/
//Count the staff members with the given role
int Dispatcher::countStaff(Role role)
{
	int count = 0;
	for (int i = 0; i < staff.Size(); ++i)
	{
		if (staff[i].getRole() == role)
		{
			count += 1;
		}
	}
	return count;
}
/* Find the index of the nth staff member,
 * counting only staff with the given role */
int Dispatcher::findStaff(Role role, int userIndex)
{
	if (userIndex < 1)
		return -1;
	int current = 0;
	for (int i = 0; i < staff.Size(); ++i)
	{
		if (staff[i].getRole() == role)
		{
			current += 1;
		}
		if (current == userIndex)
		{
			return i;
		}
	}
}
//Print the staff with the given role with numbering from 1.
void Dispatcher::printStaff(Role role)
{
	int index = 1;
	for (int i = 0; i < staff.Size(); ++i)
	{
		if (staff[i].getRole() == role)
		{
			cout << index << ": " << staff[i].getName() << endl;
			index += 1;
		}
	}
}
//Interact with the user to add a staff member
void Dispatcher::addStaff(Role role)
{
	cout << "Addding a " << role << endl;
	int day, month, year;
	String name;
	cout << "Enter names: "; cin >> name;
	cout << "Please, enter a birthdate in the format DD MM YYYY: " << endl;
	cin >> day >> month >> year;
	Date birthdate(day, month, year);
	while (birthdate.isCorrupted())
	{
		cout << "The date you enterd is not valid, plesase enter another one: " << endl;
		cin >> day >> month >> year;
		birthdate = Date(day, month, year);
	}
	staff.pushBack(MovieStaff(name, birthdate, role));
}

/*Interact with the user to choose a staff member with the given role 
  or add a new one. If a new staff member is added, it is chosen*/
int Dispatcher::chooseStaff(Role role)
{
	int index;
	cout << "Please choose " << role << endl;
	cout << "-1: Add new staff member" << endl;
	cout << "0: Cancel" << endl;
	printStaff(role);
	cin >> index;
	while(index < -1 || index > countStaff(role))
	{
	    cout << "Invalid number :( Please choose again:"; cin >> index;
	}
	cin.get();
	if (index == -1)
	{
		addStaff(role);
		return staff.Size() - 1;
	}
	return findStaff(role, index);
}
/*END OF Staff related internal functionalities*/

/*Movie related internal functionalities*/

//Count the movies that are not remakes
int Dispatcher::nonRemakesNumber()
{
	int nonRemakes = 0;
	for (int i = 0; i < movies.Size(); ++i)
	{
		if (movies[i].isNotRemake())
		{
			nonRemakes += 1;
		}
	}
	return nonRemakes;
}

/*Interact with the user to choose a movie from a numbered list
  Returns the index of the movie in the vector of movies.*/
int Dispatcher::chooseMovie()
{
	printMoviesWithIndex();
	int i;
	cout << "Enter movie index: ";
	cin >> i;
	while(i < 1 && i >movies.Size())
	{
		cout << "Invalid movie index!" << endl;
		cout << "Enter new index: ";
		cin >> i;
	}
	return i - 1;
}

/*Interact with the user to choose a movie from a numbered list.
  Ignoring remakes.
  Returns the index of the movie in the vector of movies.*/
int Dispatcher::chooseANonRemakeMovie()
{
	int remakeOf;
	cout << "Please choose if the film is a remake. Choose 0 if it is not." << endl;
	cout << "0: Not a remake" << endl;
	printMoviesWithIndex(true);
	cin >> remakeOf;
	while(remakeOf < 0 || remakeOf > nonRemakesNumber())
	{
		cout << "Invalid number :( Please choose again:"; cin >> remakeOf;
	}
	return countIgnoringRemakes(remakeOf);
}

/*Interact with the user to choose a filtering option for the movies
  Return users choice - a number from 0 to 7*/
int Dispatcher::chooseFilter()
{
	int choice;
	cout << "Filtering movies. Choose an option." << endl;
	cout << "0: Cancel" << endl;
	cout << "1: Filter by year" << endl;
	cout << "2: Filter by rating" << endl;
	cout << "3: Filter by title" << endl;
	cout << "4: Filter by genre" << endl;
	cout << "5: Filter by director" << endl;
	cout << "6: Filter by actor" << endl;
	cout << "7: Remove all current filters" << endl;
	cin >> choice;
	while (choice < 0 || choice > 7)
	{
		cout << "Invalid choice, try again: ";
		cin >> choice;
	}
	cin.get();
	return choice;
}

/*END OF Movie related internal functionalities*/

/*Filtering functions*/
void Dispatcher::filterByYear(Vector<Movie> &movies)
{
	int year;
	cout << "Enter year: "; cin >> year;
	movies = paramFilterVector(movies, isFrom, year);
}
void Dispatcher::filterByRating(Vector<Movie> &movies)
{
	double rating;
	cout << "Enter rating: "; cin >> rating;
	movies = paramFilterVector(movies, isRated, rating);
}
void Dispatcher::filterByTitle(Vector<Movie> &movies)
{
	String title;
	cout << "Enter title: "; cin >> title;
	movies = paramFilterVector(movies, isTitled, title);
}
void Dispatcher::filterByGenre(Vector<Movie> &movies)
{
	String genre;
	cout << "Enter genre: "; cin >> genre;
	movies = paramFilterVector(movies, hasGenre, genre);
}
void Dispatcher::filterByDirector(Vector<Movie> &movies)
{
	String director;
	cout << "Enter director: "; cin >> director;
	movies = paramFilterVector(movies, hasDirector, director);
}
void Dispatcher::filterByActor(Vector<Movie> &movies)
{
	String actor;
	cout << "Enter actor name: "; cin >> actor;
	movies = paramFilterVector(movies, hasActor, actor);
}
/*END OF Filtering functions*/



Dispatcher::Dispatcher() : started(false) {}

/*System functions
  start and shutdown are synchronized so that
  they are called only in the right order */
void Dispatcher::start()
{
	if (!started)
	{
		started = true;
		readUsers();
		readMovies();
		readStaff();
	}
}

void Dispatcher::shutdown()
{
	if (started)
	{
		started = false;
		updateLoggedUser();
		writeUsers();
		writeMovies();
		writeStaff();
	}
}
/*END OF System functions*/

/*User related inteface*/

/*Interact with the user so that a registration is made
  Will NOT register a user with a duplicate username
  Will NOT register a user with invalid username and password
*/
void Dispatcher::registerUser()
{
	if (thereIsUser())
		return;
	String username, password;
	cout << "-------------Registration-------------" <<endl;
	cout << "Enter username: ";
	cin >> username;
	User newUser(username, password);
	while(getUserIndex(username) != -1 || newUser.hasInvalidUsername())
	{
		cout << "Sorry, that username is already used or invalid :(" << endl;
		cout << "Please, choose another one: ";
		cin >> username;
		newUser = User(username, password);
	}
	cout << "Enter password: ";
	cin >> password;
	newUser = User(username, password);
	while(newUser.hasInvalidPassword())
	{
		cout << "Sorry, that password is not valid :(" << endl;
		cout << "Please, choose another one: ";
		cin >> password;
		newUser = User(username, password);
	}
	users.pushBack(newUser);
}

/*Interact with the user so that a login is made
  Returns true on successful login
  If 3 unsuccessful attempts are made - returns false
*/
bool Dispatcher::login()
{
	if (thereIsUser())
		return false;
	cout << "-------------Login-------------" <<endl;
	String username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;
	int errors = 0;
	int i = getUserIndex(username);
	while(i == -1 || !users[i].logIn(username, password))
	{
		errors += 1;
		if (errors == 3)
		{
			cout << "Login unsucessfull :(" << endl;
			return false;
		}
		cout << "Username and password do not match, sorry, try again." << endl;
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		i = getUserIndex(username);
	}
	loggedUser = users[i];
	cout << "Login succesfull, hello " << username << "!" << endl;
	return true;
}

void Dispatcher::logout()
{
	if (thereIsUser())
	{
		updateLoggedUser();
		loggedUser = User();
	}
}
/*END OF User related inteface*/

/*Movie related interface*/

/*Interact with the administartor to add a new movie*/
void Dispatcher::addMovie()
{
	if (!loggedAdmin())
		return;
	cout << "-------------Adding a movie-------------" <<endl;
	String title, genre;
	int year;
	cout << "Please enter the movie year: "; cin >> year; cin.get();
	cout << "Please enter the movie title: "; cin >> title;
	if (getMovieIndex(title + year) != -1)
	{
		cout << "Sorry, this movie already exists :(" << endl;
		return;
	}
	cout << "Please enter the movie genre: "; cin >> genre;
	int remakeOf = chooseANonRemakeMovie();
	String remake = "";
	if (remakeOf != -1)
	{
		remake = movies[remakeOf].getId();
	}
	int directorIndex = chooseStaff(Director);
	while (directorIndex == -1)
	{
		cout << "You MUST choose a director for the movie!" << endl;
		directorIndex = chooseStaff(Director);
	}
	String director = staff[directorIndex].getName();
	Movie newMovie(title, director, year, genre, remake);
	staff[directorIndex].addMovie(newMovie.getId());
	cout << "Adding actors: ";
	int actorIndex = chooseStaff(Actor);
	while (actorIndex != -1)
	{
		newMovie.addActor(staff[actorIndex].getName());
		staff[actorIndex].addMovie(newMovie.getId());
		actorIndex = chooseStaff(Actor);
	}
	movies.pushBack(newMovie);
}

/*Interact with the user to rate/review a film*/
bool Dispatcher::review()
{	
	if (noUser())
		return false;
	cout << "-------------Review form-------------" <<endl;
	int i = chooseMovie();
	double mark;
	cout << "Enter your rating for " << movies[i].getTitle() << ": ";
	cin >> mark;
	loggedUser.rateMovie(movies[i].getId(), mark);
	cout << "Enter your review for " << movies[i].getTitle() << ": ";

	String comment;
	cin.get();
	cin >> comment;
	loggedUser.reviewMovie(movies[i].getId(), comment);
	return true;
}

void Dispatcher::searchRemakes()
{
	cout << "Search for remakes" << endl;
	int i = chooseMovie();
	printRemakesOf(movies[i].getId());
}

void Dispatcher::searchReviews()
{
	cout << "Search reviews" << endl;
	int i = chooseMovie();
	printReviewsOf(movies[i].getId());
}

void Dispatcher::sortMovies()
{
	if (noUser())
		return;
	int choice;
	cout << "Sorting movies. Choose an option." << endl;
	cout << "1: Sort by year" << endl;
	cout << "2: Sort by rating" << endl;
	cout << "3: Sort by title" << endl;
	cout << "4: Sort by genre" << endl;
	cout << "5: Sort by director" << endl;
	cin >> choice;
	while (choice < 1 || choice > 5)
	{
		cout << "Invalid choice, try again: ";
		cin >> choice;
	}
	switch (choice)
	{
		case 1:
			sortVector(movies, compareYears, true);
			break;
		case 2:
			sortVector(movies, compareRatings, true);
			break;
		case 3:
			sortVector(movies, compareTitles);
			break;
		case 4:
			sortVector(movies, compareGenre);
			break;
		case 5:
			sortVector(movies, compareDirectors);
			break;
	}
	printMovies();
}

/*Filters the movies by the users choice.
  The vector of movies is copied so that the original is not changed.
  Once a filter is applied the corresponding movies are displayed.
  If a second filter is applied, it is chained over the first one,
  so the already filtred collection is filtred again, not the original.
  This behaviour provides powerful searching options.
  The user have the choice to remove all filters.
*/
void Dispatcher::filterMovies()
{
	if (noUser())
		return;
	Vector<Movie> filtred = movies;
	int choice = chooseFilter();
	while(choice != 0)
	{
		switch (choice)
		{
			case 1:
				filterByYear(filtred);
				break;
			case 2:
				filterByRating(filtred);
				break;
			case 3:
				filterByTitle(filtred);
				break;
			case 4:
				filterByGenre(filtred);
				break;
			case 5:
				filterByDirector(filtred);
				break;
			case 6:
				filterByActor(filtred);
				break;
			case 7:
				filtred = movies;
				break;
		}
		mapVector(filtred, printMovie);
		choice = chooseFilter();
	}
}


/*END OF Movie related interface*/