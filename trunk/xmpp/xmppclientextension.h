/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPCLIENTEXTENSION_H
#define XMPPCLIENTEXTENSION_H

#include <QObject>
#include <gloox/client.h>

using namespace gloox;

class XMPPClientExtension : public QObject
{
    Q_OBJECT
public:
    virtual ~XMPPClientExtension() {}
    virtual void attachClient(Client *client) = 0;
    virtual void detachClient(Client *client) = 0;

protected:
    XMPPClientExtension() {}
};

#endif // XMPPCLIENTEXTENSION_H
