#pragma once
#include "Date.h"

#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class Event {
private:
	std::string title;
	std::string description;
	std::string link;
	int nrPeople;
	Date date;
public:

	std::string getTitle() { return this->title; }
	std::string getDescription() { return this->description; }
	std::string getLink() { return this->link; }
	int getNrPeople() { return this->nrPeople; }
	Date& getDate() { return this->date; }

	/*
		Default constructor for Event
		Input: None
		Output: None
	*/
	Event() = default;

	/*
		Constructor for Event
		Input: title - string = title of the Event
			   description - string = description of the Event
			   link - string = link to the Event
			   nrPeople - integer = number of people attending the event
			   d - Date = date of the event
		Output: None
	*/
	Event(std::string title, std::string description, std::string link, int nrPeople, Date d);

	/*
		Copy constructor for Event
		Input: &e - reference to an Event
		Output: None
	*/
	Event(const Event& e);

	/*
		Destructor for Event
		Input: None
		Output: None
	*/
	~Event() = default;

	/*
		Equality operator(==) for two Events.
		Two Events are equal if the title and date of the events are equal.
		Input: &e - reference of the Event to be checked for equality
		Output: true if the equality stands, false otherwise
	*/
	bool operator==(const Event& e);

	/*
		Get the month of an Event
		Input: None
		Output: integer = the month of the Event
	*/
	int getMonth() { return this->date.getMonth(); }

	/*
		Get the number of people attending an Event
		Input: None
		Output: integer = number of people attending the Event
	*/
	int getAttendance() { return this->nrPeople; }

	/*
		Modify the number of people attending an Event
		Input: delta - integer = the modification
		Output: None
	*/
	void modifyAttendance(int delta);

	/*
		Greater operator(>). Checks if the current Event is greater than another one.
		An Event is greater than another one, if it happens at al ater time.
		Input: &e - reference to an Event that will be compared
		Output: true if the current Event is greater, false otherwise
	*/
	bool operator>(const Event& e);

	friend std::istream& operator>>(std::istream& is, Event& e);
	friend std::ostream& operator<<(std::ostream& os, Event& e);

	int empty() { return (this->title == ""); }
};