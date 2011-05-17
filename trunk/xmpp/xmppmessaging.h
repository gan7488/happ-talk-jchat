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

/**
 * @brief This class implements simple messaging
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

    /**
     * @brief Register handlers, and etc.
     */
    virtual void attachClient(Client *client);
    /**
     * @brief Unregister handlers, and some other functionality.
     */
    virtual void detachClient(Client *client);

    /**
     * @brief Begin messaging session.
     */
    void beginChat(const JID& target);
    /**
     * @brief End messaging session.
     */
    void endChat(const JID& target);

signals:
    /**
     * @brief Message was recieved
     */
    void chatMessageRecieved(const JID& from, const QString& msg);
    /**
     * @brief Status messages have changed.
     * @param event New event type.
     */
    void chatMessageChanged(const JID& from, MessageEventType event);
    /**
     * @brief Chat state have changed.
     * @param state New chat state.
     */
    void chatStateChanged(const JID& from, ChatStateType state);

public slots:
    /**
     * @brief Send message.
     */
    void sendChatMessage(const JID& to, const QString& msg);
    /**
     * @brief Change message status.
     * @param event New event type.
     */
    void changeMessageEvent(const JID& to, MessageEventType event);
    /**
     * @brief Change chat state.
     * @param state New chat state.
     */
    void changeChatState(const JID& to, ChatStateType state);

protected:
    /**
     * @brief Overrides of gloox::MessageHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMessage (const Message &msg, MessageSession *session=0);
    /**
     * @brief Overrides of gloox::MessageSessionHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMessageSession (MessageSession *session);
    /**
     * @brief Overrides of gloox::MessageEventHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMessageEvent (const JID &from, MessageEventType event);
    /**
     * @brief Overrides of gloox::ChatStatehadler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
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
