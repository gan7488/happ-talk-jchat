/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "xmppmessaging.h"
#include <QDebug>

/*
 Constructor and destructor
 */
XMPPMessaging::XMPPMessaging() :
    XMPPClientExtension(), m_client(0)
{
}

XMPPMessaging::~XMPPMessaging()
{
    detachClient(m_client);
}

/*
 Attach and detach client
 */
void XMPPMessaging::attachClient(Client *client)
{
    if (!client) return;
    m_client = client;
    m_client->registerMessageHandler(this);
    m_client->registerMessageSessionHandler(this);
}
void XMPPMessaging::detachClient(Client *client)
{
    if (m_client == client && client)
    {
        m_client->removeMessageHandler(this);
        m_client->registerMessageSessionHandler(0);
        m_client = 0;
    }
}

/*
 Begin messaging
 */
void XMPPMessaging::beginChat(const JID &target)
{
    /*  bare jid more abstract than full?  */
    foreach(Chat chat, m_chats)
    {
        if (chat.session && chat.session->target() == target)
        {
            qDebug() << "[beginChat] chat with jid " << target.full().c_str() << " was founded";
            return;
        }
    }
    /* jid not founded */
    m_chats.append(createChat(new MessageSession(m_client, target)));
    qDebug() << "[beginChat] chat with jid " << target.full().c_str()
            << " was not founded. created." << m_chats.count() << " in chat list";
}

/*
 Create chat
 */
XMPPMessaging::Chat XMPPMessaging::createChat(MessageSession *session)
{
    Chat chat;
    chat.session            = session;
    chat.messageEventFilter = new MessageEventFilter(chat.session);
    chat.chatStateFilter    = new ChatStateFilter(chat.session);

    chat.session->registerMessageHandler(this);
    chat.session->registerMessageFilter(chat.messageEventFilter);
    chat.messageEventFilter->registerMessageEventHandler(this);
    chat.chatStateFilter->registerChatStateHandler(this);

    return chat;
}

/*
 End messaging
 */
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

/*
 Send message or change smth.
 */
void XMPPMessaging::sendChatMessage(const JID &target, const QString &msg)
{
    beginChat(target);
    foreach(Chat chat, m_chats)
    {
        if (chat.session && chat.session->target() == target)
        {
            chat.session->send(std::string(msg.toUtf8()));
            qDebug() << "message to " << target.full().c_str() << " was sended...";
            return;
        }
    }
    qDebug() << "message to " << target.full().c_str() << " was NOT sended...";
}

void XMPPMessaging::changeMessageEvent(const JID& to, MessageEventType event)
{
    foreach(Chat chat, m_chats)
    {
        if (chat.session && chat.session->target() == to)
        {
            chat.messageEventFilter->raiseMessageEvent(event);
            qDebug() << "message event " << to.full().c_str() << " was changed...";
            return;
        }
    }
    qDebug() << "message event " << to.full().c_str() << " was NOT changed...";
}

void XMPPMessaging::changeChatState(const JID& to, ChatStateType state)
{
    foreach(Chat chat, m_chats)
    {
        if (chat.session && chat.session->target() == to)
        {
            chat.chatStateFilter->setChatState(state);
            qDebug() << "chat state " << to.full().c_str() << " was changed...";
            return;
        }
    }
    qDebug() << "chat state " << to.full().c_str() << " was NOT changed...";
}

/*
 Handlers
 */
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
    m_chats.append(createChat(session));
    qDebug() << "[handleMessageSession] chat with jid " << session->target().full().c_str()
            << " was not founded. created." << m_chats.count() << " in chat list";
}
void XMPPMessaging::handleMessageEvent(const JID &from, MessageEventType event)
{
    qDebug() << "message event from " << from.full().c_str() << event;
    emit chatMessageChanged(from, event);
}
void XMPPMessaging::handleChatState(const JID &from, ChatStateType state)
{
    qDebug() << "chat state from " << from.full().c_str() << state;
    emit chatStateChanged(from, state);
}
