#pragma once
#include <QAbstractTableModel>
#include "EventService.h"
#include "UIValidator.h"

class UserModel : public QAbstractTableModel {
private:
	EventService& es;

public:
	UserModel(EventService& es, QObject* parent = NULL);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	// stuff I've added
	std::string removeEvent(std::string title, Date d);
};