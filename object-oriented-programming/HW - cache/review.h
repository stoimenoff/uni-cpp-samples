#ifndef _REVIEW_H_
#define _REVIEW_H_

#include "mystring.h"

class Review
{
	private:
		double rating;
		String comment;
		String movieId;
	public:
		Review(const String &movieId = "");

		double getRating() const {return rating;}
		String getComment() const {return comment;}
		String getMovieId() const {return movieId;}

		bool addComment(const String &comment);
		bool addRating(double rating);
};

#endif
