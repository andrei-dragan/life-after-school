#include "EventRepo.h"
#include "RepoValidator.h"

#include <fstream>
#include <sstream>

using namespace std;

// ==================================== MAIN REPO ==================================== //
EventRepo::EventRepo(const EventRepo& er) {
	this->elems = er.elems;
}

void EventRepo::addEvent(Event e) {
	if (find(this->elems.begin(), this->elems.end(), e) != this->elems.end())
		throw RepoException(string("Event <" + e.getTitle() + "> already exists!\n"));
	this->elems.push_back(e);
}

void EventRepo::removeEvent(Event e) {
	vector<Event>::iterator it = find(this->elems.begin(), this->elems.end(), e);
	if (it != this->elems.end()) {
		this->elems.erase(it);
		return;
	}
	else 
		throw RepoException(string("Event <" + e.getTitle() + "> does not exist!\n"));
}

void EventRepo::updateEvent(Event oldE, Event newE) {
	vector<Event>::iterator it = find(this->elems.begin(), this->elems.end(), oldE);
	if (it == this->elems.end())
		throw RepoException(string("Event <" + oldE.getTitle() + "> does not exist!\n"));

	it = find(this->elems.begin(), this->elems.end(), newE);
	if (it != this->elems.end() && !(*it == oldE))
		throw RepoException(string("Event <" + newE.getTitle() + "> already exists!\n"));

	it = find(this->elems.begin(), this->elems.end(), oldE);
	*it = newE;
	this->write();
}

int EventRepo::getLength() {
	return this->elems.size();
}

Event& EventRepo::searchEvent(Event e) {
	vector<Event>::iterator it = find(this->elems.begin(), this->elems.end(), e);
	if (it != this->elems.end()) {
		return *it;
	}
	throw RepoException(string("No event matches your input! Try again!\n"));
}

Event EventRepo::getEvent(Event e) {
	vector<Event>::iterator it = find(this->elems.begin(), this->elems.end(), e);
	if (it != this->elems.end())
		return (*it);
	Event dummyE;
	return dummyE;
}

vector<Event> EventRepo::eventsByMonth(int month) {
	vector<Event>v(this->elems.size());
	vector<Event>::iterator it = copy_if(this->elems.begin(), this->elems.end(), v.begin(), [month](Event ev) {return (month == 0 || ev.getMonth() == month); });
	v.resize(distance(v.begin(), it));
	sort(v.begin(), v.end(), [](Event ev1, Event ev2) {return ev2 > ev1; });
	return v;
}

void EventRepo::modifyAttendance(Event e, int delta) {
	Event oldE = e;
	e.modifyAttendance(delta);
	this->updateEvent(oldE, e);
}

ostream& operator<<(ostream& os, EventRepo& r) {
	for (auto& ev : r.elems) {
		os << "====================================================\n";
		os << ev;
	}
	return os;
}

// ==================================== FILE REPO ==================================== //
void FileEventRepo::read() {
	Event readEvent;
	ifstream fin("NORMAL_FILE/events.txt");
	while (fin >> readEvent) {	
		if (!readEvent.empty())
			this->addEvent(readEvent);
	}
}

void FileEventRepo::write() {
	ofstream fout("NORMAL_FILE/events.txt");
	for (auto& ev : this->elems) {
		fout << ev;
	}
}

void FileEventRepo::addEvent(Event e) {
	EventRepo::addEvent(e);
	this->write();
}

void FileEventRepo::removeEvent(Event e) {
	EventRepo::removeEvent(e);
	this->write();
}

void FileEventRepo::updateEvent(Event oldE, Event newE) {
	EventRepo::updateEvent(oldE, newE);
	this->write();
}

FileEventRepo::FileEventRepo() {
	this->read();
}

// ==================================== CVS REPO ==================================== //
void CVSEventRepo::write() {
	ofstream fout("CVS_FILE/events.cvs");
	for (auto& ev : this->elems) {
		fout << ev;
	}
}

void CVSEventRepo::open() {
	this->write();
	system("notepad.exe CVS_FILE/events.cvs");
}

void CVSEventRepo::addEvent(Event e) {
	EventRepo::addEvent(e);
	this->write();
}

void CVSEventRepo::removeEvent(Event e) {
	EventRepo::removeEvent(e);
	this->write();
}

void CVSEventRepo::updateEvent(Event oldE, Event newE) {
	EventRepo::updateEvent(oldE, newE);
	this->write();
}

// ==================================== HTML REPO ==================================== //
void HTMLEventRepo::write() {
	ofstream fout("HTML_FILE/events.html");

	fout << "<!DOCTYPE html>" << '\n';
	fout << "<html>" << '\n';
	fout << "<head>" << '\n';
	fout << "<title>Events</title>" << '\n';
	fout << "</head>" << '\n';
	fout << "<body>" << '\n';
	fout << "<table border='1'>" << '\n';
	fout << "<tr>" << '\n';
	fout << "<td>Title</td>" << '\n';
	fout << "<td>Description</td>" << '\n';
	fout << "<td>Link</td>" << '\n';
	fout << "<td>Attendance</td>" << '\n';
	fout << "<td>Date</td>" << '\n';
	fout << "</tr>" << '\n';

	for (auto& ev : this->elems) {
		fout << "<tr>" << '\n';
		fout << "<td>" << ev.getTitle() << "</td>" << '\n';
		fout << "<td>" << ev.getDescription() << "</td>" << '\n';
		fout << "<td><a href = '" << ev.getLink() << "'>Link</a></td>";
		fout << "<td>" << ev.getNrPeople() << "</td>" << '\n';
		fout << "<td>" << ev.getDate().getDay() << "-" << ev.getDate().getMonth() << "-" << ev.getDate().getYear() << " " << ev.getDate().getHour() << ":" << ev.getDate().getMinute() << "</td>" << '\n';
		fout << "</tr>" << '\n';
	}

	fout << "</table>" << '\n';
	fout << "</body>" << '\n';
	fout << "</html> " << '\n';
}

void HTMLEventRepo::open() {
	this->write();
	system("start chrome file:///D:/Semester%20II/OOP/a14-912-Dragan-Andrei/LifeAfterSchool/HTML_FILE/events.html");
}

void HTMLEventRepo::addEvent(Event e) {
	EventRepo::addEvent(e);
	this->write();
}

void HTMLEventRepo::removeEvent(Event e) {
	EventRepo::removeEvent(e);
	this->write();
}

void HTMLEventRepo::updateEvent(Event oldE, Event newE) {
	EventRepo::updateEvent(oldE, newE);
	this->write();
}
