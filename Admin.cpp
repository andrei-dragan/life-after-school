#include "Admin.h"
#include <QMessageBox>
#include <algorithm>
#include <QKeyEvent>
#include <memory>
#include <vector>

using namespace std;

Admin::Admin(EventService& _es, AdminModel* _adminModel, QWidget *parent)
	: QWidget(parent), es { _es }, adminModel { _adminModel }
{
	ui.setupUi(this);
	this->ui.tableView->setModel(this->adminModel);
	this->ui.tableView->resizeColumnsToContents();

	connect(this->ui.adminAddButton, &QPushButton::clicked, this, &Admin::addEvent);
	connect(this->ui.adminDeleteButton, &QPushButton::clicked, this, &Admin::removeEvent);
	connect(this->ui.adminUpdateButton, &QPushButton::clicked, this, &Admin::updateEvent);

	connect(this->ui.undoPushButton, &QPushButton::clicked, this, &Admin::undo);
	connect(this->ui.redoPushButton, &QPushButton::clicked, this, &Admin::redo);
}

Admin::~Admin()
{
}

void Admin::keyPressEvent(QKeyEvent* e) {

	if ((e->key() == Qt::Key_Z) && QApplication::keyboardModifiers() && Qt::ControlModifier) {
		this->undo();
	}
	else if ((e->key() == Qt::Key_Y) && QApplication::keyboardModifiers() && Qt::ControlModifier) {
		this->redo();
	}
}

void Admin::addEvent() {
	int attendance = -1;

	string title = this->ui.addTitleLineEdit->text().toStdString();
	string description = this->ui.addDescriptionLineEdit->text().toStdString();
	string link = this->ui.addLinkLineEdit->text().toStdString();
	int day, month, year, hour, minute;
	Date d;

	try {
		day = stoi(this->ui.addDayLineEdit->text().toStdString());
		month = stoi(this->ui.addMonthLineEdit->text().toStdString());
		year = stoi(this->ui.addYearLineEdit->text().toStdString());
		hour = stoi(this->ui.addHourLineEdit->text().toStdString());
		minute = stoi(this->ui.addMinuteLineEdit->text().toStdString());
	}
	catch (exception& e) {
		QMessageBox* error = new QMessageBox{};
		error->setText("The inputs for the date should be integer numbers!");
		error->show();

		// clear data
		this->ui.addTitleLineEdit->clear();
		this->ui.addDescriptionLineEdit->clear();
		this->ui.addLinkLineEdit->clear();
		this->ui.addDayLineEdit->clear();
		this->ui.addMonthLineEdit->clear();
		this->ui.addYearLineEdit->clear();
		this->ui.addHourLineEdit->clear();
		this->ui.addMinuteLineEdit->clear();

		return;
	}

	try {
		Date tryDate{ day, month, year, hour, minute };
		DateValidator::validate(tryDate);
		d = tryDate;
	}
	catch (DateException& de) {
		QMessageBox* error = new QMessageBox{};
		error->setText(QString::fromStdString(de.getMessage()));
		error->show();

		// clear data
		this->ui.addTitleLineEdit->clear();
		this->ui.addDescriptionLineEdit->clear();
		this->ui.addLinkLineEdit->clear();
		this->ui.addDayLineEdit->clear();
		this->ui.addMonthLineEdit->clear();
		this->ui.addYearLineEdit->clear();
		this->ui.addHourLineEdit->clear();
		this->ui.addMinuteLineEdit->clear();

		return;
	}
	string answer = this->adminModel->addEvent(title, description, link, 0, d);

	if (answer == "") {
		Event e{ title, description, link, 0, d };
		this->action_index++;
		this->actions.erase(this->actions.begin() + this->action_index, this->actions.end());
		unique_ptr <Action> action_ptr = make_unique<ActionAdd>(ActionAdd{ e, this->es.getAdminRepo(), *this->adminModel });
		this->actions.push_back(std::move(action_ptr));
	}

	if (answer != "") {
		QMessageBox* error = new QMessageBox{};
		error->setText(QString::fromStdString(answer));
		error->show();

		// clear data
		this->ui.addTitleLineEdit->clear();
		this->ui.addDescriptionLineEdit->clear();
		this->ui.addLinkLineEdit->clear();
		this->ui.addDayLineEdit->clear();
		this->ui.addMonthLineEdit->clear();
		this->ui.addYearLineEdit->clear();
		this->ui.addHourLineEdit->clear();
		this->ui.addMinuteLineEdit->clear();

		return;
	}

	// clear data
	this->ui.addTitleLineEdit->clear();
	this->ui.addDescriptionLineEdit->clear();
	this->ui.addLinkLineEdit->clear();
	this->ui.addDayLineEdit->clear();
	this->ui.addMonthLineEdit->clear();
	this->ui.addYearLineEdit->clear();
	this->ui.addHourLineEdit->clear();
	this->ui.addMinuteLineEdit->clear();
}

vector<string> tokenizeDate(string str, char delimiter) {
	vector<string> tokens;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void Admin::removeEvent() {
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
	string dayMonthYear = tokenizeDate(dateString, ' ')[0];
	string hourMinute = tokenizeDate(dateString, ' ')[1];

	int day = stoi(tokenizeDate(dayMonthYear, '-')[0]);
	int month = stoi(tokenizeDate(dayMonthYear, '-')[1]);
	int year = stoi(tokenizeDate(dayMonthYear, '-')[2]);
	int minute = stoi(tokenizeDate(hourMinute, ':')[0]);
	int hour = stoi(tokenizeDate(hourMinute, ':')[1]);
	
	Date d{ day, month, year, minute, hour };

	// delete the event
	Event dummyE{ title, "-", "-", 0, d };
	Event e = this->es.getAdminRepo().getEvent(dummyE);
	string answer = this->adminModel->removeEvent(title, d);
	if (answer == "") {
		this->action_index++;
		this->actions.erase(this->actions.begin() + this->action_index, this->actions.end());
		unique_ptr <Action> action_ptr = make_unique<ActionRemove>(ActionRemove{ e, this->es.getAdminRepo(), *this->adminModel });
		this->actions.push_back(std::move(action_ptr));
	}
	if (answer != "") {
		QMessageBox* error = new QMessageBox{};
		error->setText(QString::fromStdString(answer));
		error->show();
		return;
	}
}

void Admin::updateEvent() {

	QModelIndexList selectedIndexes = this->ui.tableView->selectionModel()->selection().indexes();

	if (selectedIndexes.count() == 0) {
		QMessageBox* error = new QMessageBox{};
		error->setText("Select the row of the event to be updated!");
		error->show();

		this->ui.updateDescriptionLineEdit->clear();
		this->ui.updateLinkLineEdit->clear();
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
		error->setText("Select only the row of the event to be updated!");
		error->show();

		this->ui.updateDescriptionLineEdit->clear();
		this->ui.updateLinkLineEdit->clear();
		return;
	}

	if (selectedIndexes.count() != 5) {
		QMessageBox* error = new QMessageBox{};
		error->setText("Select the whole row of the event to be updated!");
		error->show();

		this->ui.updateDescriptionLineEdit->clear();
		this->ui.updateLinkLineEdit->clear();
		return;
	}

	// get the title
	string title = selectedIndexes[0].data().toString().toStdString();

	// get the date
	string dateString = selectedIndexes[4].data().toString().toStdString();
	string dayMonthYear = tokenizeDate(dateString, ' ')[0];
	string hourMinute = tokenizeDate(dateString, ' ')[1];

	int day = stoi(tokenizeDate(dayMonthYear, '-')[0]);
	int month = stoi(tokenizeDate(dayMonthYear, '-')[1]);
	int year = stoi(tokenizeDate(dayMonthYear, '-')[2]);
	int minute = stoi(tokenizeDate(hourMinute, ':')[0]);
	int hour = stoi(tokenizeDate(hourMinute, ':')[1]);

	Date d{ day, month, year, minute, hour };

	// get the other info 
	string description = this->ui.updateDescriptionLineEdit->text().toStdString();
	string link = this->ui.updateLinkLineEdit->text().toStdString();

	// update the event
	Event dummyE{ title, "-", "-", 0, d };
	Event oldE = this->es.getAdminRepo().getEvent(dummyE);
	string answer = this->adminModel->updateEvent(title, d, description, link);
	Event newE = this->es.getAdminRepo().getEvent(dummyE);
	if (answer == "") {
		this->action_index++;
		this->actions.erase(this->actions.begin() + this->action_index, this->actions.end());
		unique_ptr <Action> action_ptr = make_unique<ActionUpdate>(ActionUpdate{ oldE, newE, this->es.getAdminRepo(), *this->adminModel });
		this->actions.push_back(std::move(action_ptr));

		this->ui.updateDescriptionLineEdit->clear();
		this->ui.updateLinkLineEdit->clear();
		return;
	}
	if (answer != "") {
		QMessageBox* error = new QMessageBox{};
		error->setText(QString::fromStdString(answer));
		error->show();

		this->ui.updateDescriptionLineEdit->clear();
		this->ui.updateLinkLineEdit->clear();
		return;
	}
}

void Admin::undo() {
	if (this->action_index == -1) {
		QMessageBox* error = new QMessageBox{};
		error->setText("You can't undo anymore!");
		error->show();
	}
	else {
		this->actions[this->action_index]->executeUndo();
		this->action_index--;
	}
}

void Admin::redo() {
	if (this->action_index == this->actions.size() - 1) {
		QMessageBox* error = new QMessageBox{};
		error->setText("You can't redo anymore!");
		error->show();
	}
	else {
		this->action_index++;
		this->actions[this->action_index]->executeRedo();
	}
}