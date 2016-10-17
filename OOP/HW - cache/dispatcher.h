#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

#include <iostream>
#include <fstream>

#include "mystring.h"
#include "vector.h"
#include "movie.h"
#include "moviestaff.h"
#include "user.h"

class Dispatcher
{

	public:
		Dispatcher();
		/*System functions*/
		void start();
		void shutdown();
		/*User related inteface*/
		void registerUser();
		bool login();
		void logout();
		bool loggedAdmin() {return loggedUser.isAdmin();}
		bool thereIsUser() {return !(loggedUser.getUsername() == "");}
		bool noUser() {return loggedUser.getUsername() == "";}

		/*Movie related interface*/
		void addMovie();
		bool review();
		void sortMovies();
		void filterMovies();
		void searchRemakes();
		void searchReviews();
	private:
		User loggedUser;
		Vector<User> users;
		Vector<Movie> movies;
		Vector<MovieStaff> staff;
		bool started;

		/*File read and write functions*/
		void readUsers();
		void readMovies();
		void readStaff();

		void writeUsers();
		void writeMovies();
		void writeStaff();

		void updateLoggedUser();

		/*Internal search functions, returning index*/
		int getUserIndex(const String &username);
		int getMovieIndex(const String &movieId);
		int getStaffIndex(const String &name);
		int countIgnoringRemakes(int userIndex);

		/*Movie printing functions*/
		void printMovies();
		void printMoviesWithIndex(bool withoutRemakes = false);
		void printRemakesOf(const String &movieId);
		void printReviewsOf(const String &movieId);

		/*Staff related internal functionalities*/
		int countStaff(Role role);
		int findStaff(Role role, int userIndex);
		void printStaff(Role role);
		void addStaff(Role role);
		int chooseStaff(Role role);

		/*Movie related internal functionalities*/
		int nonRemakesNumber();
		int chooseMovie();
		int chooseANonRemakeMovie();
		int chooseFilter();
		/*Filtering functions*/
		void filterByYear(Vector<Movie> &movies);
		void filterByRating(Vector<Movie> &movies);
		void filterByTitle(Vector<Movie> &movies);
		void filterByGenre(Vector<Movie> &movies);
		void filterByDirector(Vector<Movie> &movies);
		void filterByActor(Vector<Movie> &movies);

};

#endif
