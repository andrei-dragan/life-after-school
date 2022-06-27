#include "UserEvents.h"
#include "PictureDelegate.h"
#include <QMessageBox>

using namespace std;

UserEvents::UserEvents(EventService& _es, UserModel* _userModel, QWidget *parent)
	: es{ _es }, userModel{ _userModel }, QWidget(parent)
{
	ui.setupUi(this);
	this->ui.tableView->setModel(this->userModel);

	this->ui.tableView->setItemDelegate(new PictureDelegate{});
	this->ui.tableView->resizeColumnsToContents();
	this->ui.tableView->resizeRowsToContents();

	connect(this->ui.removeUserPushButton, &QPushButton::clicked, this, &UserEvents::removeEvent);
	connect(this->ui.backPushButton, &QPushButton::clicked, this, &UserEvents::back);
}

UserEvents::~UserEvents()
{
}

vector<string> tokenizeUserDate(string str, char delimiter) {
	vector<string> tokens;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void UserEvents::back() {
	User* user = new User{ this->es, this->userModel };
	user->show();
	this->close();
}

void UserEvents::removeEvent() {
	QModelIndexList selectedIndexes = this->ui.tableView->selectionModel()->selection().indexes();

	if (selectedIndexes.count() == 0) {
		QMessageBox* error = new QMessageBox{};
		error->setText("Select the row of the event to be removed!");
		error->show();
		return;
	}

	int row = selectedIndexes[0].row();
	bool ok = 1;
	for (int i = 0; i < selectedIndexes.count(); i++) {
		QModelIndex selectedIndex = selectedIndexes[i];
		if (selectedIndex.row() != row) {
			ok = 0;
			break;
		}
	}

	if (ok == 0) {
		QMessageBox* error = new QMessageBox{};
		error->setText("Select only the row of the event to be removed!");
		error->show();
		return;
	}

	if (selectedIndexes.count() != 5) {
		QMessageBox* error = new QMessageBox{};
		error->setText("Select the whole row of the event to be removed!");
		error->show();
		return;
	}

	// get the title
	string title = selectedIndexes[0].data().toString().toStdString();

	// get the date
	string dateString = selectedIndexes[4].data().toString().toStdString();
	string dayMonthYear = tokenizeUserDate(dateString, ' ')[0];
	string hourMinute = tokenizeUserDate(dateString, ' ')[1];

	int day = stoi(tokenizeUserDate(dayMonthYear, '-')[0]);
	int month = stoi(tokenizeUserDate(dayMonthYear, '-')[1]);
	int year = stoi(tokenizeUserDate(dayMonthYear, '-')[2]);
	int minute = stoi(tokenizeUserDate(hourMinute, ':')[0]);
	int hour = stoi(tokenizeUserDate(hourMinute, ':')[1]);

	Date d{ day, month, year, minute, hour };

	// delete the event
	Event dummyE{ title, "-", "-", 0, d };
	Event e = this->es.getUserRepo().getEvent(dummyE);
	string answer = this->userModel->removeEvent(title, d);
	if (answer != "") {
		QMessageBox* error = new QMessageBox{};
		error->setText(QString::fromStdString(answer));
		error->show();
		return;
	}
}