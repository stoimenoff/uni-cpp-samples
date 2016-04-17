#include "movie.h"

Movie::Movie(const String name, const String director, int year, 
			const String genre, const String remakeOf)
	: name(name), director(director), year(year), genre(genre), id(name + year), 
	rating(0), remakeOf(remakeOf), actors(), ratedBy(0) {}

void Movie::addActor(String actorName)
{
	if (!actors.contains(actorName))
		actors.pushBack(actorName);
}

void Movie::rate(double mark)
{
	if (mark < 1 || mark > 10)
		return;
	rating += mark;
	ratedBy += 1;
}

std::ostream& operator << (std::ostream& out, const Movie& movie)
{
	out << "--------------Movie--------------" << std::endl;
	out << "Title: " << movie.getTitle() << std::endl;
	out << "Year: " << movie.getYear() << std::endl;
	if (movie.isRemake())
	{
		out << "Remake of: " << movie.getRemakeOf() << std::endl;	
	}
	out << "Director: " << movie.getDirector() << std::endl;
	out << "Rating: " << movie.getRating() << std::endl;
	out << "Rated by: " << movie.getNumberOfRates() << std::endl;
	out << "Genre: " << movie.getGenre() << std::endl;
	if (!movie.getActors().empty())
	{
		out << std::endl << "Lead actors: \n" << movie.getActors() << std::endl;
	}
	out << "---------------------------------" << std::endl;
	return out;
}

void Movie::writeToFileStream(std::ofstream &fout) const
{
	fout << name << std::endl;
	fout << year;
	fout << remakeOf << std::endl;
	fout << director << std::endl;
	fout << rating << std::endl;
	fout << ratedBy;
	fout << genre << std::endl;
	fout << actors.Size();
	for (int i = 0; i < actors.Size(); ++i)
	{
		fout << actors[i] << std::endl;
	}
}

Movie::Movie(std::ifstream &fin)
{
	fin >> name;
	fin >> year;
	fin >> remakeOf;
	fin >> director;
	fin >> rating;
	fin >> ratedBy;
	fin >> genre;
	String actorName;
	int size;
	fin >> size;
	for (int i = 0; i < size; ++i)
	{
		fin >> actorName;
		addActor(actorName);
	}
	id = name + year;
}

bool compareTitles(const Movie &m1, const Movie &m2)
{
	return m1.getTitle() < m2.getTitle();
}

bool compareRatings(const Movie &m1, const Movie &m2)
{
	if (m1.hasNotBeenRated())
		return false;
	if (m2.hasNotBeenRated())
		return true;
	return m1.getRating() < m2.getRating();
}

bool compareYears(const Movie &m1, const Movie &m2)
{
	return m1.getYear() < m2.getYear();
}

bool compareGenre(const Movie &m1, const Movie &m2)
{
	return m1.getGenre() < m2.getGenre();
}

bool compareDirectors(const Movie &m1, const Movie &m2)
{
	return m1.getDirector() < m2.getDirector();
}

Movie printMovie(Movie movie)
{
	std::cout << movie << std::endl;
	return movie;
}

bool hasActor(const Movie& m1, const String &actorName)
{
	return m1.getActors().contains(actorName);	
}

bool hasDirector(const Movie &m1, const String &directorName)
{
	return m1.getDirector() == directorName;
}

bool isRemakeOf(const Movie &m1, const String &remakeId)
{
	return m1.getRemakeOf() == remakeId;
}

bool hasGenre(const Movie& m1, const String &genre)
{
	return m1.getGenre() == genre;
}

bool isTitled(const Movie& m1, const String &title)
{
	return m1.getTitle() == title;
}

bool isRated(const Movie& m1, const double &rating)
{
	return m1.getRating() == rating;	
}
bool isFrom(const Movie& m1, const int &year)
{
	return m1.getYear() == year;
}