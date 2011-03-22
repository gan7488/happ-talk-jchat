/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef JCLIENT_H
#define JCLIENT_H

#include <gloox/disco.h>
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
#include <gloox/loghandler.h>

#include <QObject>
#include <QString>
#include <QMap>

using namespace gloox;

//class JID;
//class QString;
struct Talk
{
    MessageSession *session;
    MessageEventFilter *messageEventFilter;
};

class JClient : public QObject, PresenceHandler, ConnectionListener, MessageSessionHandler,
    MessageHandler, MessageEventHandler, ChatStateHandler, LogHandler
{
    Q_OBJECT
public:
    JClient(JID jid, const QString &pass);
    ~JClient(void);

    bool connect();
    void disconnect();

    bool beginTalk(const JID &with);
    bool endTalk(const JID &with);
public slots:
    void sendMessage(const JID &to, const QString &message);
signals:
    void connected();
    void disconnected(ConnectionError e);

    void messageRecieved(const JID &from, const QString &msg);
    //void messageEvent(const JID &from, MessageEventType);
    //void talkStateChanged(MessageEventType event);

protected:
    JClient(QObject *parent = 0);

    inline QMap<JID, Talk>::iterator findTalk(const JID& target);

    Talk newTalk(const JID &target);
    Talk newTalk(MessageSession *session);
    void disposeTalk(Talk talk);
private:
    //ConnectionListener
    virtual void onConnect();
    virtual void onDisconnect( ConnectionError e );
    virtual bool onTLSConnect( const CertInfo& info );

    //PresenceHandler
    virtual void handlePresence(const Presence& presence );

    //MessageSessionHandler
    virtual void handleMessageSession(MessageSession *session);
    //MessageHandler
    virtual void handleMessage(const Message &msg, MessageSession *session=0);
    //MessageEventHandler
    virtual void handleMessageEvent(const JID &from, MessageEventType event);
    //ChatStateHandler
    virtual void handleChatState(const JID &from, ChatStateType state);
    //LogHandler
    virtual void handleLog(LogLevel level, LogArea area, const std::string &message);

    //reciever
    void timerEvent(QTimerEvent */*event*/) { client->recv(0); }
private:
    int recvTimer;
    Client *client;
    QMap<JID, Talk> talks;
};

#endif // JCLIENT_H
