#include "ScrollEvents.h"
#include <wtypes.h>

using namespace std;

ScrollEvents::ScrollEvents(EventService& _es, int _month, UserModel* _userModel, QWidget *parent)
	: es{ _es }, month{ _month }, userModel{ _userModel }, QWidget(parent)
{
	ui.setupUi(this);
	this->eventsForGivenMonth = this->es.eventsByMonth(this->month);
	this->showEvent();

	connect(this->ui.goingPushButton, &QPushButton::clicked, this, &ScrollEvents::goingEvent);
	connect(this->ui.skipPushButton, &QPushButton::clicked, this, &ScrollEvents::skipEvent);
	connect(this->ui.backPushButton, &QPushButton::clicked, this, &ScrollEvents::back);
}

ScrollEvents::~ScrollEvents()
{
}

void ScrollEvents::showEvent() {
	// get the event
	Event ev = this->eventsForGivenMonth[0];
	string evString = ev.getTitle() + " | " + ev.getDescription() + " | " + ev.getLink() + " | " + to_string(ev.getAttendance()) + " | " +
		to_string(ev.getDate().getDay()) + "-" + to_string(ev.getDate().getMonth()) + "-" + to_string(ev.getDate().getYear()) + " " + to_string(ev.getDate().getHour()) + ":" + to_string(ev.getDate().getMinute());
	
	//open the link
	string link = ev.getLink();
	wstring stemp = std::wstring(link.begin(), link.end());
	LPCWSTR sw = stemp.c_str();
	ShellExecuteW(0, 0, sw, 0, 0, SW_SHOW);

	this->ui.eventLabel->setText(QString::fromStdString(evString));
}

void ScrollEvents::goingEvent() {
	this->es.going(this->eventsForGivenMonth[0], 1);
	this->eventsForGivenMonth.erase(this->eventsForGivenMonth.begin());

	if (this->eventsForGivenMonth.size() == 0) {
		this->back();
	}
	else {
		this->showEvent();
	}
}

void ScrollEvents::skipEvent() {
	if (this->eventsForGivenMonth.size() >= 2) {
		Event ev = this->eventsForGivenMonth[0];

		for (int i = 1; i < this->eventsForGivenMonth.size(); i++)
			this->eventsForGivenMonth[i - 1] = this->eventsForGivenMonth[i];

		this->eventsForGivenMonth[this->eventsForGivenMonth.size() - 1] = ev;
	}
	this->showEvent();
}

void ScrollEvents::back() {
	User* user = new User{ this->es, this->userModel };
	user->show();
	this->close();
}