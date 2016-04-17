#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <cstring>

#include "vector.h"
#include "mystring.h"

class Movie
{
	private:
		String id;
		String name;
		String director;
		int year;
		double rating;
		int ratedBy;
		String remakeOf;
		Vector<String> actors;
		String genre;

	public:
		Movie(const String name = "", const String director = "", 
			int year = 0, const String genre = "", const String remakeOf = "");

		void addActor(String actorName);
		void rate(double mark);

		String getId() const {return id;}
		String getTitle() const {return name;}
		String getDirector() const {return director;}
		int getYear() const {return year;}
		double getRating() const {return rating/ratedBy;}
		bool hasNotBeenRated() const {return ratedBy == 0;}
		int getNumberOfRates() const {return ratedBy;}
		bool isRemake() const {return remakeOf != "";}
		bool isNotRemake() const {return remakeOf == "";}
		String getRemakeOf() const {return remakeOf;}
		Vector<String> getActors() const {return actors;}
		String getGenre() const {return genre;}

		bool operator == (const Movie &other) const {return id == other.id;}
		bool operator != (const Movie &other) const {return id != other.id;}

		void writeToFileStream(std::ofstream &fout) const;
		Movie(std::ifstream &fin);

};

std::ostream& operator << (std::ostream& out, const Movie& movie);

bool compareTitles(const Movie &m1, const Movie &m2);
bool compareRatings(const Movie &m1, const Movie &m2);
bool compareYears(const Movie &m1, const Movie &m2);
bool compareGenre(const Movie &m1, const Movie &m2);
bool compareDirectors(const Movie &m1, const Movie &m2);
Movie printMovie(Movie movie);
bool hasActor(const Movie& m1, const String &actorName);
bool hasDirector(const Movie &m1, const String &directorName);
bool isRemakeOf(const Movie &m1, const String &remakeId);
bool hasGenre(const Movie& m1, const String &ganre);
bool isTitled(const Movie& m1, const String &title);
bool isRated(const Movie& m1, const double &rating);
bool isFrom(const Movie& m1, const int &year);

#endif //_MOVIE_H
