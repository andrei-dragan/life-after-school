#include "PictureDelegate.h"
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include "Event.h"

PictureDelegate::PictureDelegate(QWidget* parent) : QStyledItemDelegate{ parent }
{
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() != 1)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}

	QString ev = index.model()->data(index, Qt::EditRole).toString();
	if (ev.contains("sport"))
	{
		QPixmap pixMap("sport.png");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (ev.contains("entertainment"))
	{
		QPixmap pixMap("fun.png");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (ev.contains("dezvoltare"))
	{
		QPixmap pixMap("school.png");
		painter->drawPixmap(option.rect, pixMap);
	}
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == 1)
	{
		return QSize(40, 40);
	}
	return QStyledItemDelegate::sizeHint(option, index);
}
