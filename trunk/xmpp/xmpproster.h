/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPROSTER_H
#define XMPPROSTER_H

#include "xmppclientextension.h"
#include <gloox/rosterlistener.h>
#include <gloox/rostermanager.h>

using namespace gloox;

/*
 This class implements roster.
 */
class XMPPRoster : public XMPPClientExtension,
                          RosterListener
{
    Q_OBJECT
public:
    /*
     Ctors
     */
    XMPPRoster();
    virtual ~XMPPRoster();

    /*
     Attach & detach
     */
    virtual void attachClient(Client *client);
    virtual void detachClient(Client *client);

signals:
    /*
     Signals
     */
    void itemAdded (const JID &jid);
    void itemSubscribed (const JID &jid);
    void itemRemoved (const JID &jid);
    void itemUpdated (const JID &jid);
    void itemUnsubscribed (const JID &jid);
    void rosterRecieved (const Roster &roster);
    void rosterPresence (const RosterItem &item, const QString& resource, Presence::PresenceType presence, const QString& msg);
    void selfPresence (const RosterItem &item, const QString& resource, Presence::PresenceType presence, const QString& msg);
    void subscriptionRequest (const JID &jid, const QString& msg);
    void unsubscriptionRequest (const JID &jid, const QString& msg);
    void nonrosterPresence (const Presence &presence);
    void rosterError (const IQ &iq);

protected:
    /*
     Overrides of gloox::RosterListener
     */
    virtual void handleItemAdded (const JID &jid);
    virtual void handleItemSubscribed (const JID &jid);
    virtual void handleItemRemoved (const JID &jid);
    virtual void handleItemUpdated (const JID &jid);
    virtual void handleItemUnsubscribed (const JID &jid);
    virtual void handleRoster (const Roster &roster);
    virtual void handleRosterPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg);
    virtual void handleSelfPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg);
    virtual bool handleSubscriptionRequest (const JID &jid, const std::string &msg);
    virtual bool handleUnsubscriptionRequest (const JID &jid, const std::string &msg);
    virtual void handleNonrosterPresence (const Presence &presence);
    virtual void handleRosterError (const IQ &iq);

private:
    /*
     Private fields
     */
    Client  *m_client;
};

#endif // XMPPROSTER_H
