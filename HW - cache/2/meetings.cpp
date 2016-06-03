#include "meetings.h"
using std::endl;

Meeting::Meeting()
{
	start = DateTime();
	end = DateTime();
	extraNotes = "";
}

Meeting::Meeting(DateTime start, DateTime end, string extraNotes)
	: start(start), end(end), extraNotes(extraNotes) {}

int Meeting::find(string name)
{
	for(int i = 0; i < people.size(); i++)
		if(people[i] == name)
			return i;
	return -1;
}

void Meeting::addPerson(string name)
{
	if(find(name) == -1)
		people.push_back(name);
}

void Meeting::addPeople(vector<string> newPeople)
{
	for(string newPerson : newPeople)
		addPerson(newPerson);
}

void Meeting::deletePerson(string name)
{
	int i = find(name);
	if (i != -1)
		people.erase(people.begin() + i);
}

bool Meeting::contains(string name)
{
	return find(name) != -1;
}

void Meeting::print() const
{
	cout << start.getHour() << ":" << start.getMinutes() << "-"
		<< end.getHour() << ":" << end.getMinutes() << " - ";
	for (string person : people)
	{
		cout << person << ", ";
	}
	cout << extraNotes << endl;
}

bool Meeting::isOn(DateTime date) const
{
	return (date.getYear() == start.getYear()
			&& date.getMonth() == start.getMonth()
			&& date.getDay() == start.getDay());
}

void Meeting::writeTo(ofstream &out) const
{
	out << people.size() << endl;
	for (string person : people)
	{
		out << person << endl;
	}
	out << start.getYear() << endl;
	out << start.getMonth() << endl;
	out << start.getDay() << endl;
	out << start.getHour() << endl;
	out << start.getMinutes() << endl;

	out << end.getYear() << endl;
	out << end.getMonth() << endl;
	out << end.getDay() << endl;
	out << end.getHour() << endl;
	out << end.getMinutes() << endl;

	out << extraNotes << endl;
}

void Meeting::insertIn(ofstream &out) const
{
	writeTo(out);
	out << "M" << endl;
}

bool Meeting::startsAt(DateTime date) const
{
	return (start.getHour() == date.getHour()
			&& start.getMinutes() == date.getMinutes());
}

//Regular Meeting

RegularMeeting::RegularMeeting()
{
	type = "";
	note = "";
}
RegularMeeting::RegularMeeting(DateTime start, DateTime end, string extraNotes, 
			string type, string note)
	: Meeting(start, end, extraNotes), type(type), note(note) {}

void RegularMeeting::print() const
{
	Meeting::print();
}
void RegularMeeting::insertIn(ofstream &out) const
{
	writeTo(out);
	out << "RM" << endl;
	out << type << endl;
	out << note << endl;
}

Meeting* extractMeetingFrom(ifstream &in)
{
	vector<string> people;
	string person;
	int size;
	in >> size;
	in.get();
	for (int i = 0; i < size; ++i)
	{
		getline(in, person);
		people.push_back(person);
	}
	int year, month, day, hour, minutes;
	in >> year >> month >> day >> hour >> minutes;
	DateTime start(year, month, day, hour, minutes);
	in >> year >> month >> day >> hour >> minutes;
	in.get();
	DateTime end(year, month, day, hour, minutes);

	string extraNotes, identifier;
	getline(in, extraNotes);
	getline(in, identifier);
	Meeting* meeting;
	if (identifier == "M")
	{
		meeting = new Meeting(start, end, extraNotes);
	}
	if (identifier == "RM")
	{
		string type, note;
		getline(in, type);
		getline(in, note);
		meeting = new RegularMeeting(start, end, extraNotes, type, note);
	}
	meeting->addPeople(people);
	return meeting;
}

bool RegularMeeting::isOn(DateTime date) const
{
	if(type == "daily")
		return true;
	if(type == "weekly")
		return note == date.getWeekday();
	if(type == "monthly")
		return stoi(note) == date.getDay();
}