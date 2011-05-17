/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPCLIENT_H
#define XMPPCLIENT_H

#include <QObject>
#include <QList>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/jid.h>
#include "xmppclientextension.h"

using namespace gloox;

/**
 * @brief This class implements connection functions.
 * @example How to use:
 *   1) call connect()
 *   2) working
 *   3) call disconnect()
 */
class XMPPClient : public QObject,
                          ConnectionListener
{
    Q_OBJECT
public:
    /**
     * @brief Create new instance of XMPP client
     */
    XMPPClient(const JID& jid, const QString& password, int port = -1);
    /**
     * @brief Create new instance of XMPP client
     * @param server Server name or ip.
     */
    XMPPClient(const QString& server);
    virtual ~XMPPClient(void);

    /**
     * @brief Connect to server
     */
    void connect(void);
    /**
     * @brief Disconnect from the server
     */
    void disconnect(void);

    /**
     * @brief Determines whether or not authorized
     */
    bool authed() const;
    /**
     * @brief Get connection state
     */
    ConnectionState state() const;

    /**
     * @brief Attach to client an extensions.
     */
    void attach(XMPPClientExtension* ext);
    /**
     * @brief Detach to client an extensions.
     */
    void detach(XMPPClientExtension* ext);
    void operator+=(XMPPClientExtension *ext) { attach(ext); }
    void operator-=(XMPPClientExtension *ext) { detach(ext); }

    /**
     * @brief Set up a http proxy.
     */
    void setHTTPProxy(const QString& host, int port, const QString& user, const QString& pass);
    /**
     * @brief Set up a socks5 proxy
     */
    void setSOCKS5Proxy(const QString& host, int port, const QString& user, const QString& pass);

    /**
     * @brief Roster manager
     */
    RosterManager* roster() const { return m_client->rosterManager(); }

    /**
     * @brief Set your online status (available, away or more)
     */
    void setPresence (Presence::PresenceType pres) { m_client->setPresence(pres, 0); }
signals:
    /**
     * @brief Signal is raised when a connection was established.
     */
    void connected();
    /**
     * @brief Signal is raised when the connection was aborted.
     */
    void disconnected(ConnectionError e);

protected:
    /**
     * @brief Overrides of gloox::ConnectionListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void onConnect();
    /**
     * @brief Overrides of gloox::ConnectionListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void onDisconnect( ConnectionError e );
    /**
     * @brief Overrides of gloox::ConnectionListener
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual bool onTLSConnect( const CertInfo& info );

private:
    /**
     * @brief Receive packets on a timer.
     */
    void timerEvent(QTimerEvent */*event*/) { m_client->recv(0); }
    /**
     * @brief Configuration information about the xmpp client.
     */
    inline void setInfo();

protected:
    /*
     Fields
     */
    QList<XMPPClientExtension *> m_extensions;

    Client  *m_client;
private:
    int     m_recvTimer;
};

#endif // XMPPCLIENT_H
