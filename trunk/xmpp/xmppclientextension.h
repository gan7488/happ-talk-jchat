/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPCLIENTEXTENSION_H
#define XMPPCLIENTEXTENSION_H

#include <QObject>
#include <gloox/client.h>

using namespace gloox;

/*
 Base client extension.
 */
class XMPPClientExtension : public QObject
{
    Q_OBJECT
public:
    /*
     Desctructor
     */
    virtual ~XMPPClientExtension() {}

    /*
     Register or unregister handlers, and etc.
     */
    virtual void attachClient(Client *client) = 0;
    virtual void detachClient(Client *client) = 0;

protected:
    /*
     Constructor
     */
    XMPPClientExtension() {}
};

#endif // XMPPCLIENTEXTENSION_H
