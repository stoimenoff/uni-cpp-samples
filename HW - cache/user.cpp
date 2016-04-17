#include "user.h"

bool User::validatePassword(const String &password)
{
	return true;
}

bool User::validateUsername(const String &username)
{
	return true;
}

User::User(const String &username, const String &password)
{
	usernameIsValid = false;
	passwordIsValid = false;
	if (validateUsername(username))
	{
		this->username = username;
		usernameIsValid = true;
	}
	if (validatePassword(password))
	{
		this->password = password;
		passwordIsValid = true;
	}
	
}

bool User::logIn(const String &username, const String &password) const
{
	return this->username == username && this->password == password;
}

bool User::rateMovie(const String &movieId, double rating)
{
	for (int i = 0; i < reviews.Size(); ++i)
	{
		if (reviews[i].getMovieId() == movieId)
		{
			return reviews[i].addRating(rating);
		}
	}
	Review newReview(movieId);
	newReview.addRating(rating);
	reviews.pushBack(newReview);
	return true;
}

bool User::reviewMovie(const String &movieId, const String &comment)
{
	for (int i = 0; i < reviews.Size(); ++i)
	{
		if (reviews[i].getMovieId() == movieId)
		{
			return reviews[i].addComment(comment);
		}
	}
	Review newReview(movieId);
	newReview.addComment(comment);
	reviews.pushBack(newReview);
	return true;
}

std::ostream& operator << (std::ostream& out, const User& user)
{
	out << "--------------User---------------" << std::endl;
	out << "Username: " << user.getUsername() << std::endl;
	out << "Password: " << user.getPassword() << std::endl;
	if (user.reviews.Size() > 0)
	{
		out << std::endl << "Reviews: " << std::endl;
	}
	for (int i = 0; i < user.reviews.Size(); ++i)
	{
		out << "MovieId: " << user.reviews[i].getMovieId() << std::endl;
		out << "Rating: " << user.reviews[i].getRating() << std::endl;
		out << "Comment: " << user.reviews[i].getComment() << std::endl;
	}
	out << "---------------------------------" << std::endl;
	return out;
}

void User::writeToFileStream(std::ofstream &fout) const
{
	fout << username << std::endl;
	fout << password << std::endl;
	fout << reviews.Size();
	for (int i = 0; i < reviews.Size(); ++i)
	{
		fout << reviews[i].getMovieId() << std::endl;
		fout << reviews[i].getRating();
		fout << reviews[i].getComment() << std::endl;
	}
}

User::User(std::ifstream &fin)
{
	fin >> username;
	fin >> password;
	String tmpComm, tmpMovId;
	Review tmpRev;
	double tmpRating;
	int size;
	fin >> size;
	for (int i = 0; i < size; ++i)
	{
		fin >> tmpMovId;
		fin >> tmpRating;
		fin >> tmpComm;
		tmpRev = Review(tmpMovId);
		tmpRev.addComment(tmpComm);
		tmpRev.addRating(tmpRating);
		reviews.pushBack(tmpRev);
	}
	usernameIsValid = true;
	passwordIsValid = true;
}

bool User::hasReviewed(const String &movieId) const
{
	for (int i = 0; i < reviews.Size(); ++i)
	{
		if (reviews[i].getMovieId() == movieId)
			return true;
	}
	return false;
}

double User::getRatingFor(const String &movieId) const
{
	for (int i = 0; i < reviews.Size(); ++i)
	{
		if (reviews[i].getMovieId() == movieId)
			return reviews[i].getRating();
	}
	return -1;
}

String User::getReviewFor(const String &movieId) const
{
	for (int i = 0; i < reviews.Size(); ++i)
	{
		if (reviews[i].getMovieId() == movieId)
			return reviews[i].getComment();
	}
	return "";
}