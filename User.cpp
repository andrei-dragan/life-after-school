#include "User.h"
#include "UserEvents.h"
#include <QMessageBox>

User::User(EventService& _es, UserModel* _userModel, QWidget *parent)
	: es{ _es }, userModel{ _userModel }, QWidget(parent)
{
	ui.setupUi(this);

	connect(this->ui.seeFormattedUserEventsPushButton, &QPushButton::clicked, this, &User::seeFormattedEvents);
	connect(this->ui.scrollUserEventPushButton, &QPushButton::clicked, this, &User::scrollEvents);
	connect(this->ui.seeUserEventsPushButton, &QPushButton::clicked, this, &User::seeEvents);
}

User::~User()
{
}

void User::seeFormattedEvents() {
	this->es.getUserRepo().open();
}

void User::scrollEvents() {
	try {
		int month = stoi(this->ui.chooseMonthLineEdit->text().toStdString());
		if (0 <= month && month <= 12) {
			if (this->es.eventsByMonth(month).size() == 0) {
				QMessageBox* error = new QMessageBox{};
				error->setText("No more events you can attend this month!");
				error->show();
			}
			else {
				ScrollEvents* scrollEvents = new ScrollEvents{ this->es, month, this->userModel };
				scrollEvents->show();
				this->close();
			}
		}
		else {
			QMessageBox* error = new QMessageBox{};
			error->setText("Invalid month number!");
			error->show();
		}
	}
	catch (std::exception& e) {
		QMessageBox* error = new QMessageBox{};
		error->setText(QString::fromStdString(e.what()));
		error->show();
	}
}

void User::seeEvents() {
	UserEvents* userEvents = new UserEvents{ this->es, this->userModel };
	userEvents->show();
	this->close();
}