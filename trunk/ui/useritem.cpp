/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "useritem.h"
#include <QPainter>
#include <QDebug>
#include <QApplication>

UserItem::UserItem(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QSize UserItem::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return 3.1 * QStyledItemDelegate::sizeHint(option, index);
}


void UserItem::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    painter->save();

    QString nick = qvariant_cast<QString>(index.data(userNick));
    if (nick.isEmpty() || nick.isNull())
    {
        nick = qvariant_cast<QString>(index.data(userJID));
    }
    qDebug() << nick;
    QString status = qvariant_cast<QString>(index.data(userStatus));

    QString presence = qvariant_cast<QString>(index.data(userPresence));

    QFont nickf = QApplication::font();
    nickf.setBold(true);
    QFont statusf = QApplication::font();
    statusf.setPixelSize(10);

    QRect rect = option.rect;

    QPen pen;

    QIcon avatar(":/images/info.svg");

    painter->drawPixmap(QPoint(2,rect.top()),avatar.pixmap(50,50));

    pen.setColor(QColor("#000"));
    painter->setPen(pen);
    painter->setFont(nickf);
    painter->drawText(QRect(54, rect.top(), rect.width(), 17), nick);
    painter->setFont(statusf);
    pen.setColor(QColor(qRgb(155,155,155)));
    painter->setPen(pen);
    painter->drawText(QRect(54, rect.top()+17, rect.width(), rect.height()-17-15), status);
    pen.setColor(QColor(qRgb(100,100,100)));
    painter->setPen(pen);
    painter->drawText(QRect(54, rect.top()+rect.height()-15, rect.width(), 15), presence);

    painter->restore();
}
