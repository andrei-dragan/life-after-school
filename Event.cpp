#include "Event.h"

using namespace std;

Event::Event(string title, string description, string link, int nrPeople, Date d) : date(d) {
	this->title = title;
	this->description = description;
	this->link = link;
	this->nrPeople = nrPeople;
}

Event::Event(const Event& e) : date(e.date) {
	this->title = e.title;
	this->description = e.description;
	this->link = e.link;
	this->nrPeople = e.nrPeople;
}

bool Event::operator==(const Event& e) {
	return(this->title == e.title && this->date == e.date);
}

bool Event::operator>(const Event& e) {
	return (this->date > e.date);
}

void Event::modifyAttendance(int delta) {
	this->nrPeople += delta;
}

vector<string> tokenize(string str, char delimiter) {
	vector <string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

istream& operator>>(istream& is, Event& e) {
	string eventString;
	
	getline(is, eventString);
	vector <string> tokens = tokenize(eventString, ',');
	
	if (tokens.size() != 9) {
		return is;
	}

	e.title = tokens[0];
	e.description = tokens[1];
	e.link = tokens[2];
	e.nrPeople = stoi(tokens[3]);
	e.date = Date(stoi(tokens[4]), stoi(tokens[5]), stoi(tokens[6]), stoi(tokens[7]), stoi(tokens[8]));

	return is;
}

ostream& operator<<(ostream& os, Event& e) {
	if (&os == &cout) {
		os << "Title: " << e.title << "\n"
			<< "Description: " << e.description << " \n"
			<< "Link: " << e.link << "\n"
			<< "Attendance: " << e.nrPeople << "\n"
			<< "Date: " << e.date.getDay() << "-" << e.date.getMonth() << "-" << e.date.getYear() << " " << e.date.getHour() << ":" << e.date.getMinute() << "\n";
		return os;
	}
	os << e.title << "," << e.description << "," << e.link << "," << e.nrPeople << ",";
	os << e.date.getDay() << "," << e.date.getMonth() << "," << e.date.getYear() << "," << e.date.getHour() << "," << e.date.getMinute() << '\n';
	return os;
}