#pragma once
#include "Date.h"
#include "Event.h"

#include <vector>
#include <algorithm>

class EventRepo {
protected:
	std::vector<Event>elems;
public:
	/*
		Default constructor for EventRepo
		Input: None
		Output: None
	*/
	EventRepo() = default;

	/*
		Copy constructor for EventRepo
		Input: &er - reference to an EventRepo
		Output: None
	*/
	EventRepo(const EventRepo& er);

	/*
		Destructor for EventRepo
		Input: None
		Output: None
	*/
	virtual ~EventRepo() = default;

	/*
		Add an Event to the EventRepo
		Input: e - Event = event to be added
		Output: 1 if the Event was added successfully, 0 otherwise
	*/
	virtual void addEvent(Event e);

	/*
		Remove an Event from the EventRepo
		Input: e - Event = event to be removed
		Output: 1 if the Event was removed successfully, 0 otherwise
	*/
	virtual void removeEvent(Event e);

	/*
		Update an Event from the EventRepo
		Input: oldE - Event = event to be updated
			   newE - Event = the updated event
		Output: 1 if the Event was updated successfully, 0 otherwise
	*/
	virtual void updateEvent(Event oldE, Event newE);

	/*
		Get the length of the EventRepo - the number of Events inside it
		Input: None
		Output: integer representing the number of Events inside the EventRepo
	*/
	int getLength();

	/*
		Search for a certain Event inside the EventRepo
		Input: e - Event = event to be searched
		Output: string representing the formatted version of the Event, or an error message otherwise
	*/
	Event& searchEvent(Event e);

	/*
		Get an Event from the EventRepo
		Input: e - Event = event to be searched inside the EventRepo
		Output: Event representing the full version of the Event e found inside the EventRepo
	*/
	Event getEvent(Event e);

	/*
		Get all the Events according to a certain month and sort them in ascending order by the Date
		Input: month - integer = the month of the Events
		Output: DynamicArray that contains only the wanted Events, sorted accordingly
	*/
	std::vector<Event> eventsByMonth(int month);

	/*
		Modify the attendance of an Event
		Input: e - Event = the event to be modified
			   delta - integer = = the modification
		Output: None
	*/
	void modifyAttendance(Event e, int delta);

	std::vector<Event> getEvents() { return this->elems; }

	friend std::ostream& operator<<(std::ostream& os, EventRepo& r);

	/*
		Reading + writing for different repos
	*/
	virtual void read() = 0;
	virtual void write() = 0;
	virtual void open() = 0;
};

class FileEventRepo : public EventRepo {
public:
	FileEventRepo();
	void addEvent(Event e) override;
	void removeEvent(Event e) override;
	void updateEvent(Event oldE, Event newE) override;

	void read() override;
	void write() override;
	void open() override {}
};

class ConsoleEventRepo : public EventRepo {
public:
	ConsoleEventRepo() {}
	void read() override {}
	void write() override {}
	void open() override {}
};

class CVSEventRepo : public EventRepo {
public:
	CVSEventRepo() = default;
	void addEvent(Event e) override;
	void removeEvent(Event e) override;
	void updateEvent(Event oldE, Event newE) override;

	void read() override {}
	void write() override;
	void open() override;
};

class HTMLEventRepo : public EventRepo {
public:
	HTMLEventRepo() = default;
	void addEvent(Event e) override;
	void removeEvent(Event e) override;
	void updateEvent(Event oldE, Event newE) override;

	void read() override {}
	void write() override;
	void open() override;
};