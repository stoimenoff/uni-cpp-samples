#ifndef _PERSONALASSISTANT_H_
#define _PERSONALASSISTANT_H_

#include "meetings.h"

class PersonalAssistant
{
	private:
		string bossName;
		vector<Meeting*> meetings;
		void readMeetings();
		bool isFree(string name, DateTime start, DateTime end) const;
		bool areFree(vector<string> people, DateTime start, DateTime end) const;
		void printSuggestion(DateTime start, DateTime end, string person) const;
		
		PersonalAssistant(string bossName);

		//Singleton
		PersonalAssistant(const PersonalAssistant &) {};
		PersonalAssistant& operator= (const PersonalAssistant &) {};

		static PersonalAssistant* mInstance;

	public:
		static PersonalAssistant* instance(string bossName = "");

		void showMeetings(DateTime date) const;
		string createMeeting(DateTime start, int duration, 
			vector<string> people, string extraNotes);
		string createRegularMeeting(DateTime start, int duration, 
			vector<string> people, string extraNotes, string type, string note);
		string removeMeeting(DateTime date);
		string suggestMeetingTime(DateTime start, int duration, string person) const;
		string processCommand(string command);
		void writeChanges() const;
		~PersonalAssistant();

};

#endif