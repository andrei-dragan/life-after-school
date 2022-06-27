#pragma once

#include <QWidget>
#include "ui_UserFile.h"
#include "UserModel.h"

class UserFile : public QWidget
{
	Q_OBJECT

public:
	UserFile(EventService& es, EventService& secondaryEs, QWidget* parent = Q_NULLPTR);
	~UserFile();

private:
	EventService& es;
	EventService& secondaryEs;
	Ui::UserFile ui;

public:
	void htmlUser();
	void cvsUser();
};
