#pragma once

#include <QWidget>
#include "ui_ScrollEvents.h"
#include "User.h"


class ScrollEvents : public QWidget
{
	Q_OBJECT

public:
	ScrollEvents(EventService &es, int month, UserModel* userModel, QWidget *parent = Q_NULLPTR);
	~ScrollEvents();

private:
	EventService& es;
	int month;
	UserModel* userModel;
	Ui::ScrollEvents ui;
	std::vector<Event>eventsForGivenMonth;

public:
	void showEvent();
	void goingEvent();
	void skipEvent();
	void back();
};
