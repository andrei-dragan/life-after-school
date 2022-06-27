#pragma once

#include <QWidget>
#include "ui_UserEvents.h"
#include "User.h"

class UserEvents : public QWidget
{
	Q_OBJECT

public:
	UserEvents(EventService& es, UserModel* userModel, QWidget *parent = Q_NULLPTR);
	~UserEvents();

private:
	EventService& es;
	UserModel* userModel;
	Ui::UserEvents ui;

public:
	void removeEvent();
	void back();
};
