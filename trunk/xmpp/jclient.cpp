/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "jclient.h"
#include <QtDebug>
#include <QMessageBox>

JClient::JClient(QObject *parent)
    :QObject(parent)
{

}

void JClient::handlePresence(const Presence &presence)
{
    qDebug() << "handlePresence from " << QString::fromStdString(presence.from().bare())
            << " to " << QString::fromStdString(presence.to().bare()) << " lang "
            << QString::fromStdString(presence.xmlLang())
            << " status " << QString::fromStdString(presence.status()) << endl;
}

void JClient::onConnect()
{
    qDebug() << "onConnect" << endl;
}
void JClient::onDisconnect( ConnectionError e )
{
    qDebug() << "onDisconnect " << e << endl;
}

bool JClient::onTLSConnect( const CertInfo& info )
{
    qDebug() << "onTLSConnect issuer" << QString::fromStdString(info.issuer)
            << " server " << QString::fromStdString(info.server) << endl;
    return true;
}

void JClient::connect(JID &jid, const QString &password)
{
    client = new Client(jid, password.toStdString());
    client->registerConnectionListener( this );
    client->registerPresenceHandler( this );
    client->registerMessageSessionHandler(this);
    if (client->connect(false))
    {
        timerId = startTimer(2000);
    }
}
void JClient::timerEvent(QTimerEvent *event)
{
    if (client == 0) return;
    client->recv(1000);
}

void JClient::handleMessageSession(MessageSession *session)
{
    qDebug() << "handleMessageSession target " << session->target().bare().c_str()
            << "session pointer " << session << endl;
    client->disposeMessageSession( m_session );
    m_session = session;
    m_session->registerMessageHandler( this );
    m_messageEventFilter = new MessageEventFilter( m_session );
    m_messageEventFilter->registerMessageEventHandler( this );
    m_chatStateFilter = new ChatStateFilter( m_session );
    m_chatStateFilter->registerChatStateHandler( this );

}
void JClient::handleMessage(const Message &msg, MessageSession *session)
{
    qDebug() << "handleMessage message " << msg.body().c_str() << " from "
            << msg.from().bare().c_str() << "subtype " << msg.subtype() <<
            " subject " << msg.subject().c_str() << " thread " << msg.thread().c_str() <<
            " session pointer " << session << endl;
    m_messageEventFilter->raiseMessageEvent( MessageEventDisplayed );

    m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
    m_chatStateFilter->setChatState( ChatStateComposing );
    sleep(2);
    QString re = "You said:\n> %1\nI like that statement.";
    re.arg(QString::fromStdString(msg.body()));
    QString sub = "RE: %1";
    sub.arg(QString::fromStdString(msg.subject()));
    m_session->send(re.toStdString(), sub.toStdString());

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
