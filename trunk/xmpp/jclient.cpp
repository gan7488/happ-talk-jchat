/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "jclient.h"
#include <QtDebug>
#include <QMessageBox>

JClient::JClient(JID jid, const QString &pass)
{
    client = new Client(jid, pass.toStdString());

    client->disco()->setVersion("jchat", "0.1");
    client->disco()->setIdentity("client", "IM");

    client->registerConnectionListener(this);
    client->registerPresenceHandler(this);
    client->registerMessageSessionHandler(this);
    //client->registerMessageHandler(this);
}
JClient::JClient(QObject *parent)
    :QObject(parent) ,client(0)
{

}

JClient::~JClient()
{
    disconnect();
    delete client;
}

bool JClient::connect()
{
    bool connected = client->connect(false);
    if (connected) recvTimer = startTimer(100);
    return connected;
}

void JClient::disconnect()
{
    client->disconnect();
}

bool JClient::beginTalk(const JID &with)
{
    QMap<JID, Talk>::iterator i = findTalk(with);
    if (i == talks.end())
    {
        talks.insert(with, newTalk(with));
        return true;
    }
    //exist! & verify session or not?
    return false;
}

void JClient::sendMessage(const JID &to, const QString &message)
{
    QMap<JID, Talk>::iterator i = findTalk(to);
    if (i == talks.end())
    {
        qDebug() << to.full().c_str();
        talks.insert(to, newTalk(to));
    }
    Talk talk = i.value();
    talk.session->registerMessageHandler(this);
    talk.session->send(message.toStdString());
}

bool JClient::endTalk(const JID &with)
{
    QMap<JID, Talk>::iterator i = findTalk(with);
    if (i != talks.end())
    {
        disposeTalk(i.value());
        talks.erase(i);
        return true;
    }
    return false;
}
QMap<JID, Talk>::iterator JClient::findTalk(const JID &target)
{
    QMap<JID, Talk>::iterator i = talks.begin();
    while (i != talks.end())
    {
        if (i.key() == target) break;
        i++;
    }
    qDebug() << "searching " << target.full().c_str();
    if (i != talks.end())
    {
        Talk talk = i.value();
        JID jid = i.key();
        qDebug() << "key " << jid.full().c_str() << " value " << talk.session->target().full().c_str();
    }
    return i;
}
Talk JClient::newTalk(const JID &target)
{
    qDebug() << " new talk by jid";
    MessageSession *session = new MessageSession(client, target);
    return newTalk(session);
}

Talk JClient::newTalk(MessageSession *session)
{
    qDebug() << " new talk by session";
    Talk talk;
    talk.session = session;
    talk.session->registerMessageHandler(this);
    talk.messageEventFilter = new MessageEventFilter(session);
    talk.session->registerMessageFilter(talk.messageEventFilter);
    return talk;
}

void JClient::disposeTalk(Talk talk)
{
    qDebug() << "dispose talk";
    talk.session->disposeMessageFilter(talk.messageEventFilter);
    client->disposeMessageSession(talk.session);
}



void JClient::onConnect()
{
    qDebug() << "connected" << endl;
    emit connected();
}
void JClient::onDisconnect( ConnectionError e )
{
    qDebug() << "disconnect with error #" << e << endl;
    emit disconnected(e);
}
bool JClient::onTLSConnect( const CertInfo& info )
{
    qDebug() << "certificate recieved: issuer" << QString::fromStdString(info.issuer)
            << " server " << QString::fromStdString(info.server) << endl;
    return true;
}

void JClient::handlePresence(const Presence &presence)
{
    qDebug() << "handlePresence from " << QString::fromStdString(presence.from().bare())
            << " to " << QString::fromStdString(presence.to().bare())
            << " lang " << QString::fromStdString(presence.xmlLang())
            << " status " << QString::fromStdString(presence.status()) << endl;
}


void JClient::handleMessageSession(MessageSession *session)
{
    qDebug() << "handleMessageSession target " << session->target().bare().c_str()
            << "session pointer " << session << talks.count() << endl;
    QMap<JID, Talk>::iterator i = findTalk(session->target());
    if (i == talks.end())
    {
        talks.insert(session->target(), newTalk(session));
        return;
    }
    Talk talk = i.value();
    if (talk.session == session) return;
    disposeTalk(talk);
    i.value() = newTalk(session);
}
void JClient::handleMessage(const Message &msg, MessageSession *session)
{
    qDebug() << "handleMessage message " << msg.body().c_str() << " from "
            << msg.from().bare().c_str() << "subtype " << msg.subtype() <<
            " subject " << msg.subject().c_str() << " thread " << msg.thread().c_str() <<
            " session pointer " << session << talks.count() << endl;
    //if (session == 0) return;
    emit messageRecieved(msg.from(), QString::fromUtf8(msg.body().c_str()));
}
void JClient::handleMessageEvent(const JID &from, MessageEventType event)
{
    qDebug() << "handleMessageEvent from " << QString::fromStdString(from.bare())
            << " type " << event << endl;
}
void JClient::handleChatState(const JID &from, ChatStateType state)
{
    qDebug() << "handleChatState from " << QString::fromStdString(from.bare())
            << " state " << state << endl;
}
void JClient::handleLog( LogLevel level, LogArea area, const std::string& message )
{
    qDebug() << "handleLog level " << level << " area " << area << " message " << message.c_str();
}
