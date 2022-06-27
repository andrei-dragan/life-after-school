#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LifeAfterSchool.h"
#include "EventService.h"
#include "AdminModel.h"
#include "UserModel.h"

class LifeAfterSchool : public QMainWindow
{
    Q_OBJECT

public:
    LifeAfterSchool(EventService& es, EventService& secondaryEs, QWidget* parent = Q_NULLPTR);

private:
    EventService& es;
    EventService& secondaryEs;
    AdminModel* adminModel;
    Ui::LifeAfterSchoolClass ui;

public:
    void openAdmin();
    void openUser();
};
