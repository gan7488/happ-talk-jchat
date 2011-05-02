/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "xmppclient.h"
#include <QDebug>
#include <gloox/connectiontcpclient.h>
#include <gloox/connectionhttpproxy.h>
#include <gloox/connectionsocks5proxy.h>
#include <gloox/disco.h>

/*
 Constructors and destructor.
 */
XMPPClient::XMPPClient(const JID &jid, const QString &password, int port)
{
    m_client = new Client(jid, password.toStdString(), port);
    m_client->registerConnectionListener(this);

    setInfo();
}
XMPPClient::XMPPClient(const QString &server)
{
    m_client = new Client(server.toStdString());
    m_client->registerConnectionListener(this);

    setInfo();
}
void XMPPClient::setInfo()
{
    m_client->disco()->setVersion( "proto-xmpp-core", "alfa");
    m_client->disco()->setIdentity( "client", "im" );
}

/*
 Delete or detach extensions here?
 */
XMPPClient::~XMPPClient(void)
{
    disconnect();
    foreach(XMPPClientExtension *ext, m_extensions)
        if (ext) delete ext;
    //if (m_client)
     //   delete m_client;
}

/*
 Connection functions.
 */
void XMPPClient::connect(void)
{
    qDebug() << "connect";
    bool connected = m_client->connect(false);
    if (connected) m_recvTimer = startTimer(100);
}
void XMPPClient::disconnect(void)
{
    qDebug() << "disconnect";
    m_client->disconnect();
}
bool XMPPClient::authed() const
{
    return m_client->authed();
}
ConnectionState XMPPClient::state() const
{
    return m_client->state();
}
/*
 Attach and detach functions.
 */
void XMPPClient::attach(XMPPClientExtension *ext)
{
    if (m_extensions.contains(ext) || !ext) return;
    m_extensions.append(ext);
    ext->attachClient(m_client);
    qDebug() << "somebody was attached";
}
void XMPPClient::detach(XMPPClientExtension *ext)
{
    if (m_extensions.removeOne(ext))
        ext->detachClient(m_client);
    qDebug() << "somebody was detached";
}
/*
 Proxies
 */
void XMPPClient::setHTTPProxy(const QString &host, int port, const QString &user, const QString &pass)
{
    //save server and port
    const std::string& xmppHost = m_client->server();
    int xmppPort = m_client->port();

    //proxy
    ConnectionTCPClient* conn0 = new ConnectionTCPClient( m_client->logInstance(), host.toStdString(), port );
    //xmpp host
    ConnectionHTTPProxy* conn1 = new ConnectionHTTPProxy( m_client, conn0, m_client->logInstance(), xmppHost, xmppPort );

    //proxy auth
    conn1->setProxyAuth(user.toStdString(), pass.toStdString());
    //set connection implementation
    m_client->setConnectionImpl( conn1 );
}
void XMPPClient::setSOCKS5Proxy(const QString &host, int port, const QString &user, const QString &pass)
{
    //save server and port
    const std::string& xmppHost = m_client->server();
    int xmppPort = m_client->port();

    //proxy
    ConnectionTCPClient* conn0 = new ConnectionTCPClient( m_client->logInstance(), host.toStdString(), port );
    //xmpp host
    ConnectionSOCKS5Proxy* conn1 = new ConnectionSOCKS5Proxy( m_client, conn0, m_client->logInstance(), xmppHost, xmppPort );

    //proxy auth
    conn1->setProxyAuth(user.toStdString(), pass.toStdString());
    //set connection implementation
    m_client->setConnectionImpl( conn1 );
}

/*
 ConnectionListener methods goes here
 */
void XMPPClient::onConnect()
{
    qDebug() << "connected";
    emit connected();
}
void XMPPClient::onDisconnect(ConnectionError e)
{
    qDebug() << "disconnected";
    killTimer(m_recvTimer);
    emit disconnected(e);
}
bool XMPPClient::onTLSConnect(const CertInfo &info)
{
    return true;
}
