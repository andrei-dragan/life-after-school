#include "AdminModel.h"
#include <QFont>
#include <QMessageBox>

using namespace std;

int toInt(string number) {
	int nr = 0;
	for (int i = 0; i < number.length(); i++) {

		if (i == 9) {
			throw UIException("The number is too big!");
		}

		if ('0' <= number[i] && number[i] <= '9') {
			nr = nr * 10 + number[i] - '0';
		}
		else {
			throw UIException("This is not a number!");
		}
	}
	return nr;
}

vector<string> tokenizeDate(string dateString) {
	vector <string> result;
	stringstream ss(dateString);
	string token;
	while (getline(ss, token, '-'))
		result.push_back(token);
	while (getline(ss, token, ' '))
		result.push_back(token);
	while (getline(ss, token, ':'))
		result.push_back(token);

	return result;
}

AdminModel::AdminModel(EventService& _es, QObject* parent) : es{ _es }, QAbstractTableModel(parent) {}

int AdminModel::rowCount(const QModelIndex& parent) const {
	return this->es.getAdminRepo().getEvents().size();
}

int AdminModel::columnCount(const QModelIndex& parent) const {
	return 5;
}

QVariant AdminModel::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int column = index.column();

	vector<Event>events = this->es.getAdminRepo().getEvents();
	if (row == events.size()) {
		return QVariant{};
	}

	Event event = events[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		if (column == 0) {
			return QString::fromStdString(event.getTitle());
		}
		else if (column == 1) {
			return QString::fromStdString(event.getDescription());
		}
		else if (column == 2) {
			return QString::fromStdString(event.getLink());
		}
		else if (column == 3) {
			return QString::fromStdString(to_string(event.getAttendance()));
		}
		else if (column == 4) {
			string date = "";
			date += to_string(event.getDate().getDay()) + "-" + to_string(event.getDate().getMonth()) + "-" + to_string(event.getDate().getYear()) + " ";
			date += to_string(event.getDate().getHour()) + ":" + to_string(event.getDate().getMinute());
			return QString::fromStdString(date);
		}
	}
	if (role == Qt::BackgroundRole) {
		if (row % 2 == 0) {
			return QBrush{ QColor {0, 250, 154} };
		}
	}
	if (role == Qt::SizeHintRole) {
		QSize s{ 200, 40 };
		return s;
	}
	return QVariant{};
}

QVariant AdminModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0: 
				return QString{ "Title" }; 
			case 1:
				return QString{ "Description" };
			case 2:
				return QString{ "Link" };
			case 3:
				return QString{ "Attendace" };
			case 4:
				return QString{ "Date" };
			default:
				break;
			}
		}

		if (orientation == Qt::Vertical) {
			return QString::fromStdString(" " + to_string(section) + " ");
		}
	} 
	if (role == Qt::FontRole) {
		QFont f{ "Nuninto", 12 };
		f.setBold(true);
		return f;
	}
	return QVariant{};
}	

Qt::ItemFlags AdminModel::flags(const QModelIndex& index) const {
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

string AdminModel::addEvent(string title, string description, string link, int nrPeople, Date d) {
	int rows = this->rowCount();
	this->beginInsertRows(QModelIndex{}, rows, rows);

	try {
		this->es.addEvent(title, description, link, nrPeople, d);
	}
	catch (RepoException& re) {
		return re.getMessage();
	}

	this->endInsertRows();

	return "";
}

string AdminModel::removeEvent(string title, Date d) {
	int row = 0;
	vector<Event> events = this->es.getAdminRepo().getEvents();
	for (int i = 0; i < events.size(); i++) {
		if (title == events[i].getTitle() && d == events[i].getDate())
			row = i;
	}

	this->beginRemoveRows(QModelIndex{}, row, row);
	try {
		this->es.removeAdminEvent(title, d);
	}
	catch (RepoException& re) {
		return re.getMessage();
	}

	this->endRemoveRows();

	return "";
}

string AdminModel::updateEvent(string title, Date d, string description, string link) {
	int row = 0;
	vector<Event> events = this->es.getAdminRepo().getEvents();
	for (int i = 0; i < events.size(); i++) {
		if (title == events[i].getTitle() && d == events[i].getDate())
			row = i;
	}

	try {
		this->es.updateEvent(title, d, title, description, link, d);
	}
	catch (RepoException& re) {
		return re.getMessage();
	}
	dataChanged(QModelIndex{}, QModelIndex{});

	return "";
}
