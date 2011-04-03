/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPMESSAGING_H
#define XMPPMESSAGING_H

#include "xmppclientextension.h"
#include <QList>
#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/messageeventfilter.h>
#include <gloox/messageeventhandler.h>
#include <gloox/messagesession.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/chatstatefilter.h>
#include <gloox/chatstatehandler.h>

using namespace gloox;

class XMPPMessaging : public XMPPClientExtension, MessageHandler, MessageSessionHandler
{
    Q_OBJECT
    struct Chat
    {
        MessageSession      *session;
        MessageEventFilter  *messageEventFilter;
        ChatStateFilter     *chatStateFilter;
    };

public:
    XMPPMessaging();

    virtual void attachClient(Client *client);
    virtual void detachClient(Client *client);

    void beginChat(const JID& target);
    void endChat(const JID& target);
signals:
    void chatMessageRecieved(const JID& target, const QString& msg);

public slots:
    void sendChatMessage(const JID& target, const QString& msg);

protected:
    /*  Overrides of MessageHandler */
    virtual void handleMessage (const Message &msg, MessageSession *session=0);
    /*  Overrides of MessageSessionHandler  */
    virtual void handleMessageSession (MessageSession *session);

private:
    Client *m_client;
    QList<Chat> m_chats;

};

#endif // XMPPMESSAGING_H
