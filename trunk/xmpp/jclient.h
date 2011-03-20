/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef JCLIENT_H
#define JCLIENT_H

#include <gloox/presence.h>
#include <gloox/presencehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/messageeventhandler.h>
#include <gloox/chatstatehandler.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messageeventfilter.h>
#include <gloox/chatstatefilter.h>
#include <gloox/client.h>
#include <gloox/jid.h>

#include <QObject>
#include <QString>

using namespace gloox;

//class JID;
//class QString;

class JClient : public QObject, PresenceHandler, ConnectionListener, MessageSessionHandler,
    MessageHandler, MessageEventHandler, ChatStateHandler
{
    Q_OBJECT
public:
    explicit JClient(QObject *parent = 0);

    //PresenceHandler
    virtual void handlePresence(const Presence& presence );
    //ConnectionListener
    virtual void onConnect();
    virtual void onDisconnect( ConnectionError e );
    virtual bool onTLSConnect( const CertInfo& info );
    //MessageSessionHandler
    virtual void handleMessageSession(MessageSession *session);
    //MessageHandler
    virtual void handleMessage(const Message &msg, MessageSession *session=0);
    //MessageEventHandler
    virtual void handleMessageEvent(const JID &from, MessageEventType event);
    //ChatStateHandler
    virtual void handleChatState(const JID &from, ChatStateType state);



    void connect(JID &jid, const QString &password);

protected:
    void timerEvent(QTimerEvent *event);

private:
    int timerId;
    Client *client;
    MessageSession *m_session;
    MessageEventFilter *m_messageEventFilter;
    ChatStateFilter *m_chatStateFilter;
};

#endif // JCLIENT_H
