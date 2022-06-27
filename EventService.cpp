#include "EventService.h"

using namespace std;

EventService::EventService(EventRepo* adminRepo, EventRepo* userRepo) {
	this->adminRepo = adminRepo;
	this->userRepo = userRepo;
}

void EventService::addEvent(string title, string description, string link, int nrPeople, Date d) {
	Event e(title, description, link, nrPeople, d);
	this->adminRepo->addEvent(e);
}

void EventService::removeAdminEvent(string title, Date d) {
	Event e(title, "-", "-", 0, d);
	this->adminRepo->removeEvent(e);

	try {
		this->userRepo->removeEvent(e);
	}
	catch (RepoException& ee) {}
}

void EventService::removeUserEvent(string title, Date d) {
	Event dummy(title, "-", "-", 0, d);
	this->userRepo->removeEvent(dummy);
	Event e = this->adminRepo->getEvent(dummy);
	this->adminRepo->modifyAttendance(e, -1);
}

void EventService::updateEvent(string oldTitle, Date oldD, string newTitle, string newDescription, string newLink, Date newD) {
	Event dummyE{ oldTitle, "-", "-", 0, oldD };
	this->adminRepo->searchEvent(dummyE);
	Event e1 = this->adminRepo->getEvent(dummyE);
	Event e2(newTitle, newDescription, newLink, e1.getAttendance(), newD);
	this->adminRepo->updateEvent(e1, e2);

	try {
		this->userRepo->searchEvent(e1);
		this->userRepo->updateEvent(e1, e2);
	}
	catch (RepoException& ee) {}
}

Event& EventService::searchEvent(string title, Date d) {
	Event e(title, "-", "-", 0, d);
	return this->adminRepo->searchEvent(e);
}

EventRepo& EventService::getAdminRepo() {
	return *(this->adminRepo);
}

EventRepo& EventService::getUserRepo() {
	return *(this->userRepo);
}

void EventService::going(Event e, int delta) {
	this->adminRepo->modifyAttendance(e, delta);
	this->userRepo->addEvent(e);
	this->userRepo->modifyAttendance(e, delta);
}

EventService::~EventService() {
	delete this->adminRepo;
	delete this->userRepo;
}

vector<Event> EventService::eventsByMonth(int month) {
	vector<Event>ans;
	for (auto ev : this->adminRepo->eventsByMonth(month)) {
		try {
			this->userRepo->searchEvent(ev);
		}
		catch (RepoException& re) {
			ans.push_back(ev);
		}
	}
	return ans;
}