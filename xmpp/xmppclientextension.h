/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPCLIENTEXTENSION_H
#define XMPPCLIENTEXTENSION_H

#include <QObject>
#include <gloox/client.h>

using namespace gloox;

/**
 * @brief Base client extension.
 */
class XMPPClientExtension : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Desctructor
     */
    virtual ~XMPPClientExtension() {}

    /**
     * @brief Register handlers, and etc.
     */
    virtual void attachClient(Client *client) = 0;
    /**
     * @brief Unregister handlers, and some other functionality.
     */
    virtual void detachClient(Client *client) = 0;

protected:
    /**
     * @brief Constructor
     */
    XMPPClientExtension() {}
};

#endif // XMPPCLIENTEXTENSION_H
