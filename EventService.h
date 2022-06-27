#pragma once
#include "EventRepo.h"
#include "RepoValidator.h"

#include <stdexcept>
#include <assert.h>

class EventService {
private:
	EventRepo* adminRepo;
	EventRepo* userRepo;
public:
	/*
		Default constructor for EventService
		Input: None
		Output: None
	*/
	EventService() = default;

	/*
		Constructor for EventService
		Input: &adminRepo - reference to EventRepo = the admin's repository
			   &userRepo - reference to EventRepo = the user's repository
		Output: None
	*/
	EventService(EventRepo* adminRepo, EventRepo* userRepo);

	/*
		Destructor for EventService
		Input: None
		Output: None
	*/
	~EventService();

	/*
		Copy constructor for EventService
		Input: &es - const reference to EventService
		Output: None
	*/
	EventService(const EventService& es) = default;

	/*
		Add an Event to the admin's repository
		Input: title - string = title of the Event
			   description - string = description of the Event
			   link - string = link to the Event
			   nrPeople - integer = number of people attending the Event
			   d - Date = date of the event
		Output: 1 if the operation was successful, 0 otherwise
	*/
	void addEvent(std::string title, std::string description, std::string link, int nrPeople, Date d);

	/*
		Remove an Event from the admin's repository
		Input: title - stirng = title of the Event
			   d - Date = date of the Event
		Output: 1 if the operation was successful, 0 otherwise
	*/
	void removeAdminEvent(std::string title, Date d);

	/*
		Remove an Event from the user's repository
		Input: title - stirng = title of the Event
			   d - Date = date of the Event
		Output: 1 if the operation was successful, 0 otherwise
	*/
	void removeUserEvent(std::string title, Date d);

	/*
		Update an Event inside the admin's repository
		Input: oldTitle - string = current title of the Event
			   oldD - Date = current date of the Event
			   newTitle - string = updated title of the Event
			   newDescription - string = updated description of the Event
			   newLink - string = updated link to the Event
			   newD - Date = updated date of the Event
	*/
	void updateEvent(std::string oldTitle, Date oldD, std::string newTitle, std::string newDescription, std::string newLink, Date newD);

	/*
		Search for an Event
		Input: title - string = title of the Event
			   d - Date = date of the Event
		Output: string representing the formatted version of the Event, or an error message if the Event was not found
	*/
	Event& searchEvent(std::string title, Date d);

	/*
		Get the admin's repository
		Input: None
		Output: EventRepo reference to the admin's repository
	*/
	EventRepo& getAdminRepo();

	/*
		Get the user's repository
		Input: None
		Output: EventRepo reference to the user's repository
	*/
	EventRepo& getUserRepo();

	/*
		Attend/Unattend an Event
		Input: e - Event = the event that will be attended
			   delta - integer = +1 / -1 depending on the decision made by the user
		Output: None
	*/
	void going(Event e, int delta);

	std::vector<Event>eventsByMonth(int month);
};