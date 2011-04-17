/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include <QDebug>
#include "xmpproster.h"
#include <gloox/rostermanager.h>

/*
 Ctors
 */
XMPPRoster::XMPPRoster() :
    XMPPClientExtension(), m_client(0)
{
}
XMPPRoster::~XMPPRoster()
{
    detachClient(m_client);
}

/*
 Attach & detach
 */
void XMPPRoster::attachClient(Client *client)
{
    if (!client) return;
    m_client = client;
    m_client->rosterManager()->registerRosterListener(this);
}

void XMPPRoster::detachClient(Client *client)
{
    if (m_client == client && client)
    {
        m_client->rosterManager()->removeRosterListener();
        m_client = 0;
    }
}

/*
 RosterListener methods goes here
 */
void XMPPRoster::handleItemAdded (const JID &jid)
{
    qDebug() << "item added in roster";
    emit itemAdded(jid);
}

void XMPPRoster::handleItemSubscribed (const JID &jid)
{
    qDebug() << "item subscribed";
    emit itemSubscribed(jid);
}

void XMPPRoster::handleItemRemoved (const JID &jid)
{
    qDebug() << "item removed from roster";
    emit itemRemoved(jid);
}

void XMPPRoster::handleItemUpdated (const JID &jid)
{
    qDebug() << "item updated";
    emit itemUpdated(jid);
}

void XMPPRoster::handleItemUnsubscribed (const JID &jid)
{
    qDebug() << "item unsubscribed";
    emit itemUnsubscribed(jid);
}

void XMPPRoster::handleRoster (const Roster &roster)
{
    qDebug() << "roster recieved";
    emit rosterRecieved(roster);
}

void XMPPRoster::handleRosterPresence
        (const RosterItem &item, const std::string &resource,
         Presence::PresenceType presence, const std::string &msg)
{
    qDebug() << "roster presence";
    emit rosterPresence(item, QString::fromUtf8(resource.c_str()),
                        presence, QString::fromUtf8(msg.c_str()));
}

void XMPPRoster::handleSelfPresence
        (const RosterItem &item, const std::string &resource,
         Presence::PresenceType presence, const std::string &msg)
{
    qDebug() << "self presence";
    emit selfPresence(item, QString::fromUtf8(resource.c_str()),
                      presence, QString::fromUtf8(msg.c_str()));
}

bool XMPPRoster::handleSubscriptionRequest
        (const JID &jid, const std::string &msg)
{
    qDebug() << "subsription request";
    emit subscriptionRequest(jid, QString::fromUtf8(msg.c_str()));
    /*
      The return value of this function must be ignored.
     */
    return false;
}

bool XMPPRoster::handleUnsubscriptionRequest
        (const JID &jid, const std::string &msg)
{
    qDebug() << "unsubscription request";
    emit unsubscriptionRequest(jid, QString::fromUtf8(msg.c_str()));
    /*
      The return value of this function must be ignored.
     */
    return false;
}

void XMPPRoster::handleNonrosterPresence (const Presence &presence)
{
    qDebug() << "nonroster presence";
    emit nonrosterPresence(presence);
}

void XMPPRoster::handleRosterError (const IQ &iq)
{
    qDebug() << "roster error occured";
    emit rosterError(iq);
}
