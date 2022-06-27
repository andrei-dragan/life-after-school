#pragma once

#include <QWidget>
#include "ui_Admin.h"
#include "EventService.h"
#include "AdminModel.h"
#include "Action.h"

class Admin : public QWidget
{
	Q_OBJECT

public:
	Admin(EventService& es, AdminModel* adminModel, QWidget *parent = Q_NULLPTR);
	void keyPressEvent(QKeyEvent* e);
	~Admin();

private:
	AdminModel* adminModel;
	EventService& es;
	Ui::Admin ui;
	std::vector<std::unique_ptr<Action>> actions;
	int action_index = -1;

public:
	void addEvent();
	void removeEvent();
	void updateEvent();
	void undo();
	void redo();
};
