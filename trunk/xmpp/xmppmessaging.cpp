/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "xmppmessaging.h"
#include <QDebug>

XMPPMessaging::XMPPMessaging() :
    XMPPClientExtension()
{
}

void XMPPMessaging::attachClient(Client *client)
{
    m_client = client;
    m_client->registerMessageHandler(this);
    m_client->registerMessageSessionHandler(this);
}
void XMPPMessaging::detachClient(Client *client)
{
    if (m_client == client)
    {
        m_client->removeMessageHandler(this);
        m_client->registerMessageSessionHandler(0);
        m_client = 0;
    }
}

void XMPPMessaging::beginChat(const JID &target)
{
    /*  bare jid more abstract than full  */
    foreach(Chat chat, m_chats)
    {
        if (chat.session && chat.session->target() == target)
        {
            qDebug() << "[beginChat] chat with jid " << target.full().c_str() << " was founded";
            return;
        }
    }
    /* jid not founded */
    Chat chat;
    chat.session            = new MessageSession(m_client, target);
    chat.messageEventFilter = new MessageEventFilter(chat.session);
    chat.chatStateFilter    = new ChatStateFilter(chat.session);

    chat.session->registerMessageHandler(this);
    chat.session->registerMessageFilter(chat.messageEventFilter);

    m_chats.append(chat);
    qDebug() << "[beginChat] chat with jid " << target.full().c_str()
            << " was not founded. created." << m_chats.count() << " in chat list";
}

void XMPPMessaging::endChat(const JID &target)
{
    /*  search full jid  */
    int i;
    for(i = 0; i < m_chats.count(); i++)
    {
        if (m_chats[i].session && m_chats[i].session->target() == target)
            break;
    }
    qDebug() << "begin disposing a chat at" << i << " position from list. in list:" << m_chats.count();
    if (i >= m_chats.count()) return;

    Chat chat = m_chats[i];
    m_chats.removeAt(i);
    /*  Disposing elements  */
    chat.session->disposeMessageFilter(chat.messageEventFilter);
    m_client->disposeMessageSession(chat.session);
    qDebug() << "[endChat] chat with jid " << target.full().c_str()
            << " was founded. disposed."<< m_chats.count() << " in chat list";
}
void XMPPMessaging::sendChatMessage(const JID &target, const QString &msg)
{
    beginChat(target);
    foreach(Chat chat, m_chats)
    {
        if (chat.session && chat.session->target() == target)
        {
            chat.session->send(msg.toStdString());
            qDebug() << "message to " << target.full().c_str() << " was sended...";
            return;
        }
    }
    qDebug() << "message to " << target.full().c_str() << " was NOT sended...";
}

void XMPPMessaging::handleMessage(const Message &msg, MessageSession *session)
{
    emit chatMessageRecieved(msg.from(),QString::fromUtf8(msg.body().c_str()));
}
void XMPPMessaging::handleMessageSession(MessageSession *session)
{
    foreach(Chat chat, m_chats)
    {
        if (chat.session->target() == session->target())
        {
            qDebug() << "[handleMessageSession] JID == JID";
            if (chat.session != session)
                qDebug() << "[handleMessageSession] SESSION != SESSION, but JID == JID";
            return;
        }
    }

    /* jid not founded */
    Chat chat;
    chat.session            = session;
    chat.messageEventFilter = new MessageEventFilter(chat.session);
    chat.chatStateFilter    = new ChatStateFilter(chat.session);

    chat.session->registerMessageHandler(this);
    chat.session->registerMessageFilter(chat.messageEventFilter);

    m_chats.append(chat);
    qDebug() << "[handleMessageSession] chat with jid " << session->target().full().c_str()
            << " was not founded. created." << m_chats.count() << " in chat list";
}
