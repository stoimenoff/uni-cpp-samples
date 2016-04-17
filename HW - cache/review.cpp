#include "review.h"

Review::Review(const String &movieId) 
	: movieId(movieId), comment(""), rating(0) {}

bool Review::addComment(const String &comment)
{
	if (this->comment == "")
	{
		this->comment = comment;
		return true;
	}
	return false;
}

bool Review::addRating(double rating)
{
	if (rating < 1 || rating > 10 || this->rating != 0)
		return false;

	this->rating = rating;
	return true;
}