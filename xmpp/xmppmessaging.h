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

/*
 This class implements simple messaging
 */
class XMPPMessaging : public XMPPClientExtension,
                             MessageHandler,
                             MessageSessionHandler,
                             MessageEventHandler,
                             ChatStateHandler
{
    Q_OBJECT
    struct Chat
    {
        MessageSession      *session;
        MessageEventFilter  *messageEventFilter;
        ChatStateFilter     *chatStateFilter;
    };

public:
    /*
     Constructor and destructor
     */
    XMPPMessaging();
    virtual ~XMPPMessaging();

    /*
     Attach and detach client
     */
    virtual void attachClient(Client *client);
    virtual void detachClient(Client *client);

    /*
     Begin or end messaging session
     */
    void beginChat(const JID& target);
    void endChat(const JID& target);

signals:
    /*
     Something changed or recieved
     */
    void chatMessageRecieved(const JID& from, const QString& msg);
    void chatMessageChanged(const JID& from, MessageEventType event);
    void chatStateChanged(const JID& from, ChatStateType state);

public slots:
    /*
     Send something or change smth.
     */
    void sendChatMessage(const JID& to, const QString& msg);
    void changeMessageEvent(const JID& to, MessageEventType event);
    void changeChatState(const JID& to, ChatStateType state);

protected:
    /*
     Overrides of MessageHandler
     */
    virtual void handleMessage (const Message &msg, MessageSession *session=0);
    /*
     Overrides of MessageSessionHandler
     */
    virtual void handleMessageSession (MessageSession *session);
    /*
     Overrides of MessageEventHandler
     */
    virtual void handleMessageEvent (const JID &from, MessageEventType event);
    /*
     Overrides of ChatStatehadler
     */
    virtual void handleChatState (const JID &from, ChatStateType state);

private:
    Chat createChat(MessageSession *session);
    /*
     Private field
     */
    Client*     m_client;
    QList<Chat> m_chats;
};

#endif // XMPPMESSAGING_H
