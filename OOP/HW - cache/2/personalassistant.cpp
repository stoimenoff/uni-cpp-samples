#include "personalassistant.h"
using std::endl;

string& removeTrailing(string &str);
string cutOneWord(string &str, char beginSep = ' ',
	char endSep = ' ', int pos = 0);
vector<string> cutPeople(string &command);
vector<string> getParams(string command);

const string meetingsFile = "meetings";

//Singleton
PersonalAssistant* PersonalAssistant::mInstance = NULL;

PersonalAssistant* PersonalAssistant::instance(string bossName)
{
	if(!mInstance)
		mInstance = new PersonalAssistant(bossName);
	return mInstance;
}

void PersonalAssistant::readMeetings()
{
	int size;
	ifstream file(meetingsFile);
	if(file.peek() == std::ifstream::traits_type::eof())
	{
		return;
	}
	file >> size;
	for (int i = 0; i < size; ++i)
	{
		meetings.push_back(extractMeetingFrom(file));
	}
	file.close();
}

void PersonalAssistant::writeChanges() const
{
	ofstream file(meetingsFile);
	file << meetings.size() << endl;
	for (int i = 0; i < meetings.size(); ++i)
	{
		meetings[i]->insertIn(file);
	}
	file.close();
}

PersonalAssistant::PersonalAssistant(string bossName)
	: bossName(bossName) {readMeetings();}

PersonalAssistant::~PersonalAssistant()
{
	for(Meeting* meeting : meetings)
		delete meeting;	
}

bool PersonalAssistant::isFree(string name, DateTime start, DateTime end) const
{
	for(Meeting* meeting : meetings)
		if(meeting->contains(name) && meeting->intersectsWith(start, end))
			return false;
	return true;
}

bool PersonalAssistant::areFree(vector<string> people, DateTime start, DateTime end) const
{
	for(string person : people)
		if(!isFree(person, start, end))
			return false;
	return true;
}

void PersonalAssistant::showMeetings(DateTime date) const
{
	for(Meeting* meeting : meetings)
		if(meeting->isOn(date) && meeting->contains(bossName))
			meeting->print();
}

string PersonalAssistant::removeMeeting(DateTime date)
{
	for(int i = 0; i < meetings.size(); i++)
	{
		if(meetings[i]->isOn(date) && meetings[i]->startsAt(date)
			&& meetings[i]->contains(bossName))
		{
			meetings[i]->deletePerson(bossName);
			if(meetings[i]->peopleNumber() < 2)
			{
				delete meetings[i];
				meetings.erase(meetings.begin() + i);
				return "Meeting removed successfully";
			}
			return "You were successfully removed from the meeting";
		}
	}
	return "No such meeting";
}

string PersonalAssistant::createMeeting(DateTime start, int duration, 
			vector<string> people, string extraNotes)
{
	if(duration % 30 != 0)
		return "Bad meeting duration, It should be a multiple of 30 minutes";

	DateTime end = start + duration;

	if(start.timeIsInvalid() || end.timeIsInvalid())
		return "Bad meeting start or end";

	if(!isFree(bossName, start, end))
		return "You are not free in that period of time";

	if(!areFree(people, start, end))
		return "One or more of the people are busy";

	Meeting* newMeeting = new Meeting(start, end, extraNotes);
	for(string person : people)
		newMeeting->addPerson(person);

	newMeeting->addPerson(bossName);
	meetings.push_back(newMeeting);
	return "Meeting created successfully";
}

string PersonalAssistant::createRegularMeeting(DateTime start, int duration, 
			vector<string> people, string extraNotes, string type, string note)
{
	if(duration % 30 != 0)
		return "Bad meeting duration, It should be a multiple of 30 minutes";

	DateTime end = start + duration;

	if(start.timeIsInvalid() || end.timeIsInvalid())
		return "Bad meeting start or end";

	if(type != "daily" && type != "weekly" && type != "monthly" )
		return "Invalid meeting type";

	if(type == "weekly")
		if(!DateTime::isWeekDay(note))
			return "Invalid week day";

	if(type == "monthly")
		if(stoi(note) < 0 || stoi(note) > 28)
			return "Invalid month day";

	if(!isFree(bossName, start, end))
		return "You are not free in that period of time";

	if(!areFree(people, start, end))
		return "One or more of the people are busy";

	Meeting* newMeeting = new RegularMeeting(start, end, extraNotes, type, note);
	for (int i = 0; i < people.size(); ++i)
	{
		newMeeting->addPerson(people[i]);
	}
	newMeeting->addPerson(bossName);
	meetings.push_back(newMeeting);
	return "Regular meeting created successfully";
}

void PersonalAssistant::printSuggestion(DateTime start, DateTime end, string person) const
{
	if(end.isTimeValid())
	{
		if(isFree(bossName, start, end) && isFree(person, start, end))
		{
			cout << start.getHour() << ":" << start.getMinutes() << "-";
			cout << end.getHour() << ":" << end.getMinutes() << ", ";
		}
	}
}

string PersonalAssistant::suggestMeetingTime(DateTime start, int duration, string person) const
{
	if(duration % 30 != 0)
		return "Bad meeting duration, It should be a multiple of 30 minutes";

	DateTime end;
	for (int hour = 8; hour < 20; ++hour)
	{
		start.setTime(hour, 0);
		end = start + duration;
		printSuggestion(start, end, person);

		start.setTime(hour, 30);
		end = start + duration;
		printSuggestion(start, end, person);
	}

	return "End of suggestions";

}

string PersonalAssistant::processCommand(string command)
{
	vector<string> params = getParams(command);
	string cmd = params[0];
	if(cmd == "cm")
	{
		if(!DateTime::validateDateString(params[1]))
			return "Invalid date format";
		if(!DateTime::validateTimeString(params[2]))
			return "Invalid time format";
		if(!DateTime::validateIntervalString(params[3]))
		{
			std::cout << "|" << params[3] << "|" << std::endl;
			return "Invalid duration";
		}
		DateTime date(params[1]);
		date.setTime(params[2]);
		int duration = stoi(params[3]);
		vector<string> people(params.begin() + 4, params.end() - 1);
		string extraNotes = params.back();
		return createMeeting(date, duration, people, extraNotes);
	}
	if(cmd == "crm")
	{
		if(!DateTime::validateTimeString(params[1]))
			return "Invalid time format";
		if(!DateTime::validateIntervalString(params[2]))
			return "Invalid duration";
		DateTime date;
		date.setTime(params[1]);
		int duration = stoi(params[2]);
		string type = params[3];
		string note = params[4];
		vector<string> people(params.begin() + 5, params.end() - 1);
		string extraNotes = params.back();
		return createRegularMeeting(date, duration, people, extraNotes, type, note);
	}
	if(cmd == "rm")
	{
		if(!DateTime::validateDateString(params[1]))
			return "Invalid date format";
		if(!DateTime::validateTimeString(params[2]))
			return "Invalid time format";
		DateTime date(params[1]);
		date.setTime(params[2]);
		return removeMeeting(date);
	}
	if(cmd == "sm")
	{
		if(!DateTime::validateDateString(params[1]))
			return "Invalid date format";
		DateTime date(params[1]);
		showMeetings(date);
		return "End of meetings";
	}
	if(cmd == "smt")
	{
		if(!DateTime::validateDateString(params[1]))
			return "Invalid date format";
		if(!DateTime::validateIntervalString(params[2]))
			return "Invalid duration";
		DateTime date(params[1]);
		int duration = stoi(params[2]);
		string person = params[3];
		return suggestMeetingTime(date, duration, person);
	}
	return "Unrecognised command";
}

//string shits

string& removeTrailing(string &str)
{
	while(str.front() == ' ')
		str.erase(str.begin());
	while(str.back() == ' ')
		str.pop_back();
	return str;
}

string cutOneWord(string &str, char beginSep, char endSep, int pos)
{
	int begin = str.find(beginSep, pos);
	if(begin == string::npos)
		return "";
	begin += 1;
	int end = str.find(endSep, begin);
	if (end == string::npos)
		return "";
	end -= 1;
	string word = str.substr(begin, end - begin + 1);
	str.erase(pos, end - pos + 1);
	return word;
}

vector<string> cutPeople(string &command)
{
	vector<string> people;
	string person = cutOneWord(command, ' ', ',');
	while(person != "")
	{
		people.push_back(person);
		command.erase(command.begin());
		person = cutOneWord(command, ' ', ',');
	}
	return people;
}

vector<string> getParams(string command)
{
	vector<string> params = {"No such command"};
	if(command.substr(0, 22) == "create regular meeting")
	{
		params[0] = "crm";
		command.erase(0, 22);
		string timeString = cutOneWord(command);
		string intervalString = cutOneWord(command);
		string typeString = cutOneWord(command);
		string noteString = "";
		if (!(typeString == "daily"))
			noteString = cutOneWord(command);
		params.push_back(removeTrailing(timeString));
		params.push_back(removeTrailing(intervalString));
		params.push_back(removeTrailing(typeString));
		params.push_back(removeTrailing(noteString));
		vector<string> people = cutPeople(command);
		params.insert(params.end(), people.begin(), people.end());
		params.push_back(removeTrailing(command)); //extraNotes
	}
	if(command.substr(0, 14) == "create meeting")
	{
		params[0] = "cm";
		command.erase(0, 14);
		string dateString = cutOneWord(command);
		string timeString = cutOneWord(command);
		string intervalString = cutOneWord(command);
		params.push_back(removeTrailing(dateString));
		params.push_back(removeTrailing(timeString));
		params.push_back(removeTrailing(intervalString));
		vector<string> people = cutPeople(command);
		params.insert(params.end(), people.begin(), people.end());
		params.push_back(removeTrailing(command)); //extraNotes
	}
	if(command.substr(0, 13) == "show meetings" && command.size() == 22)
	{
		params[0] = "sm";
		command.erase(0, 14);
		params.push_back(removeTrailing(command)); //date
	}
	if(command.substr(0, 14) == "remove meeting" && command.size() == 29)
	{
		params[0] = "rm";
		command.erase(0, 14);
		string dateString = cutOneWord(command);
		params.push_back(removeTrailing(dateString));
		params.push_back(removeTrailing(command)); //time
	}
	if(command.substr(0, 20) == "suggest meeting time")
	{
		params[0] = "smt";
		command.erase(0, 20);
		string dateString = cutOneWord(command);
		string intervalString = cutOneWord(command);
		params.push_back(removeTrailing(dateString));
		params.push_back(removeTrailing(intervalString));
		params.push_back(removeTrailing(command)); //person
	}
	return params;
}