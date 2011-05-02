/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef USERITEM_H
#define USERITEM_H

#include <QStyledItemDelegate>

class UserItem : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit UserItem(QObject *parent = 0);


    enum ItemRole
    {
        userNick = Qt::UserRole + 100,
        userStatus = Qt::UserRole + 101,
        userJID = Qt::UserRole + 102,
        userPresence = Qt::UserRole + 103
    };

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                       const QModelIndex &index) const;

signals:

public slots:

};

#endif // USERITEM_H
