#ifndef _USER_H_
#define _USER_H_

#include "vector.h"
#include "mystring.h"
#include "review.h"

class User
{
	private:
		String username;
		String password;
		Vector<Review> reviews;
		bool usernameIsValid;
		bool passwordIsValid;

		bool validatePassword(const String &password);
		bool validateUsername(const String &username);
	public:
		User(const String &username = "", const String &password = "");

		String getUsername() const {return username;}
		String getPassword() const {return password;}
		bool isAdmin() const {return username == "Admin";}
		bool logIn(const String &username, const String &password) const;

		bool rateMovie(const String &movieId, double rating);
		bool reviewMovie(const String &movieId, const String &comment);

		User(std::ifstream &fin);
		void writeToFileStream(std::ofstream &fout) const;

		bool hasInvalidUsername() const {return !usernameIsValid;}
		bool hasInvalidPassword() const {return !passwordIsValid;}

		bool hasReviewed(const String &movieId) const;
		double getRatingFor(const String &movieId) const;
		String getReviewFor(const String &movieId) const;

		friend std::ostream& operator << (std::ostream& out, const User& user);
};


#endif
