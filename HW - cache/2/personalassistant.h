#ifndef _PERSONALASSISTANT_H_
#define _PERSONALASSISTANT_H_

#include "meetings.h"

class PersonalAssistant
{
	private:
		string bossName;
		vector<Meeting*> meetings;
		void readMeetings();
	public:
		PersonalAssistant(string bossName);
		void showMeetings(DateTime date) const;
		bool createMeeting(DateTime start, int duration, 
			vector<string> people, string extraNotes);
		bool createRegularMeeting(DateTime start, int duration, 
			vector<string> people, string extraNotes, string type, string note);
		bool removeMeeting(DateTime date);
		string processCommand(string command);
		void writeChanges() const;

};

#endif