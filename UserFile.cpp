#include "UserFile.h"
#include "User.h"

UserFile::UserFile(EventService& _es, EventService& _secondaryEs, QWidget *parent)
	: es{ _es }, secondaryEs{_secondaryEs}, QWidget(parent)
{
	ui.setupUi(this);

	// connect the buttons
	QObject::connect(this->ui.htmlUserButton, &QPushButton::clicked, this, &UserFile::htmlUser);
	QObject::connect(this->ui.cvsUserButton, &QPushButton::clicked, this, &UserFile::cvsUser);
}

UserFile::~UserFile()
{
}

void UserFile::htmlUser() {
	UserModel* userModel = new UserModel{ this->es };
	User* user = new User{ this->es, userModel };
	user->show();
	this->close();
}

void UserFile::cvsUser() {
	UserModel* userModel = new UserModel{ this->secondaryEs };
	User* user = new User{ this->secondaryEs, userModel };
	user->show();
	this->close();
}