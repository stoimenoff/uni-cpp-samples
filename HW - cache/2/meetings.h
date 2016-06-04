#ifndef _MEETINGS_H_
#define _MEETINGS_H_

#include "datetime.h"
#include <fstream>
#include <iostream>
#include <vector>

using std::vector;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::cout;
using std::endl;

class Meeting
{
	protected:
		vector<string> people;
		DateTime start;
		DateTime end;
		string extraNotes;
		int find(string name);
		void writeTo(ofstream &out) const;
	public:
		Meeting();
		Meeting(DateTime start, DateTime end, string extraNotes);

		void addPerson(string name);
		void addPeople(vector<string> newPeople);
		void deletePerson(string name);
		bool contains(string name);
		int peopleNumber() const {return people.size();}

		bool startsAt(DateTime date) const;

		DateTime startTime() const {return start;}
		DateTime endTime() const {return end;}

		virtual void print() const;
		virtual void insertIn(ofstream &out) const;
		virtual bool isOn(DateTime date) const;
		virtual string getType() const {return "meeting";}

		virtual bool intersectsWith(DateTime start, DateTime end) const;
};

class RegularMeeting : public Meeting
{
	protected:
		string type;
		string note;
	public:
		RegularMeeting();
		RegularMeeting(DateTime start, DateTime end, string extraNotes, 
			string type, string note);
		
		virtual string getType() const {return type;}
		string getNote() const {return note;}

		virtual void print() const;
		virtual void insertIn(ofstream &out) const;
		virtual bool isOn(DateTime date) const;

		virtual bool intersectsWith(DateTime mStart, DateTime mEnd) const;
};

Meeting* extractMeetingFrom(ifstream &in);

#endif