/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPCLIENT_H
#define XMPPCLIENT_H

#include <QObject>

class XMPPClient : public QObject
{
    Q_OBJECT
public:
    explicit XMPPClient(QObject *parent = 0);

signals:

public slots:

};

#endif // XMPPCLIENT_H
