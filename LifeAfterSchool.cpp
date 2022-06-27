#include "LifeAfterSchool.h"
#include "Admin.h"
#include "UserFile.h"
#include <QObject>

LifeAfterSchool::LifeAfterSchool(EventService& _es, EventService& _secondaryEs, QWidget* parent)
    : QMainWindow(parent), secondaryEs{_secondaryEs}, es{ _es }
{
    ui.setupUi(this);
    
    // connect the buttons
    QObject::connect(this->ui.loginAdminButton, &QPushButton::clicked, this, &LifeAfterSchool::openAdmin);
    QObject::connect(this->ui.loginUserButton, &QPushButton::clicked, this, &LifeAfterSchool::openUser);

    // init the models
    this->adminModel = new AdminModel{ this->es };
}


void LifeAfterSchool::openAdmin() {
    Admin* adminUI = new Admin{ this->es, this->adminModel };
    adminUI->show();
    this->close();
}

void LifeAfterSchool::openUser() {
    UserFile* userFile = new UserFile{ this->es, this->secondaryEs };
    userFile->show();
    this->close();
}