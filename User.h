#pragma once

#include <QWidget>
#include "ui_User.h"
#include "UserModel.h"
#include "ScrollEvents.h"

class User : public QWidget
{
	Q_OBJECT

public:
	User(EventService& es, UserModel* userModel, QWidget *parent = Q_NULLPTR);
	~User();

private:
	EventService& es;
	UserModel* userModel;
	Ui::User ui;

public:
	void seeFormattedEvents();
	void scrollEvents();
	void seeEvents();
};
