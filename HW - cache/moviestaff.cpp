#include "moviestaff.h"

MovieStaff::MovieStaff(String name, Date birthdate, Role role)
	:name(name), birthdate(birthdate), role(role) {}

void MovieStaff::addMovie(const String &movieId)
{
	if(movieIds.contains(movieId))
	{
		return;
	}
	movieIds.pushBack(movieId);
}

std::ostream& operator << (std::ostream& out, const MovieStaff& staff)
{
	out << "------------MovieStaff------------" << std::endl;
	out << "Name: " << staff.getName() << std::endl;
	out << "Birthdate: " << staff.getBirthdate() << std::endl;
	out << "Role: " << staff.getRole() << std::endl;
	if (staff.movieIds.Size() > 0)
	{
		out << "Movies: " << std::endl;
	}
	for (int i = 0; i < staff.movieIds.Size(); ++i)
	{
		out << staff.movieIds[i] << std::endl;
	}
	out << "----------------------------------" << std::endl;
	return out;
}

void MovieStaff::writeToFileStream(std::ofstream &fout) const
{
	fout << name << std::endl;
	fout << birthdate.Day() << std::endl;
	fout << birthdate.Month() << std::endl;
	fout << birthdate.Year() << std::endl;
	fout << movieIds.Size();
	if (movieIds.Size() == 0)
	{
		fout << std::endl;
	}
	for (int i = 0; i < movieIds.Size(); ++i)
	{
		fout << movieIds[i] << std::endl;
	}
	writeRoleToFileStream(fout, role);
}
MovieStaff::MovieStaff(std::ifstream &fin)
{
	fin >> name;
	String movieId;
	int day, month, year, size;
	fin >> day >> month >> year >> size;
	birthdate = Date(day, month, year);
	for (int i = 0; i < size; ++i)
	{
		fin >> movieId;
		addMovie(movieId);
	}
	role = readRoleFromFileStream(fin);
}