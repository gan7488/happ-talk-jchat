/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPROSTER_H
#define XMPPROSTER_H

#include "xmppclientextension.h"
#include <gloox/rosterlistener.h>
#include <gloox/rostermanager.h>

using namespace gloox;

/**
 * @brief This class implements roster functionality.
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

    /**
     * @brief Register handlers, and etc.
     */
    virtual void attachClient(Client *client);
    /**
     * @brief Unregister handlers, and some other functionality.
     */
    virtual void detachClient(Client *client);

signals:
    /**
     * @brief Occurs when item was added to roster.
     */
    void itemAdded (const JID &jid);
    /**
     * @brief Occurs when item was subscribed
     */
    void itemSubscribed (const JID &jid);
    /**
     * @brief Occurs when item was removed.
     */
    void itemRemoved (const JID &jid);
    /**
     * @brief Occurs when item was updated.
     */
    void itemUpdated (const JID &jid);
    /**
     * @brief Occurs when item was unsubscribed.
     */
    void itemUnsubscribed (const JID &jid);
    /**
     * @brief Occurs when roster was recieved from server.
     */
    void rosterRecieved (const Roster &roster);
    /**
     * @brief Occurs when presence recieved for an item that in roster.
     */
    void rosterPresence (const RosterItem &item, const QString& resource, Presence::PresenceType presence, const QString& msg);
    /**
     * @brief Occurs when self presence was recieved.
     */
    void selfPresence (const RosterItem &item, const QString& resource, Presence::PresenceType presence, const QString& msg);
    /**
     * @brief Occurs when subscription was requested.
     */
    void subscriptionRequest (const JID &jid, const QString& msg);
    /**
     * @brief Occurs when unsubscription was recieved.
     */
    void unsubscriptionRequest (const JID &jid, const QString& msg);
    /**
     * @brief Occcurs when presence recieved for an item that not in roster.
     */
    void nonrosterPresence (const Presence &presence);
    /**
     * @brief Occurs on error with roster.
     */
    void rosterError (const IQ &iq);

protected:
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleItemAdded (const JID &jid);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleItemSubscribed (const JID &jid);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleItemRemoved (const JID &jid);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleItemUpdated (const JID &jid);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleItemUnsubscribed (const JID &jid);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleRoster (const Roster &roster);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleRosterPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleSelfPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual bool handleSubscriptionRequest (const JID &jid, const std::string &msg);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual bool handleUnsubscriptionRequest (const JID &jid, const std::string &msg);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleNonrosterPresence (const Presence &presence);
    /**
     * @brief Overrides of gloox::RosterListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleRosterError (const IQ &iq);

private:
    /*
     Private fields
     */
    Client  *m_client;
};

#endif // XMPPROSTER_H
