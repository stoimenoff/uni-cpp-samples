#ifndef _MOVIESTAFF_H_
#define _MOVIESTAFF_H_

#include "vector.h"
#include "mystring.h"
#include "date.h"
#include "role.h"

class MovieStaff
{
	private:
		String name;
		Date birthdate;
		Vector<String> movieIds;
		Role role;
	public:
		MovieStaff(String name = "", Date birthdate = Date(), Role role = Actor);

		void addMovie(const String &movieId);

		String getName() const {return name;}
		Date getBirthdate() const {return birthdate;}
		Vector<String> getMovieIds() const {return movieIds;}
		Role getRole() const {return role;}

		bool is(const Role role) const {return this->role == role;}

		void writeToFileStream(std::ofstream &fout) const;
		MovieStaff(std::ifstream &fin);

		friend std::ostream& operator << (std::ostream& out, const MovieStaff& staff);
};


#endif
