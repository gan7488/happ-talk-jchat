/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "xmppclient.h"
#include <QDebug>
#include <gloox/connectiontcpclient.h>
#include <gloox/connectionhttpproxy.h>
#include <gloox/connectionsocks5proxy.h>

XMPPClient::XMPPClient(const JID &jid, const QString &password, int port)
{
    m_client = new Client(jid, password.toStdString(), port);
    m_client->registerConnectionListener(this);
}
XMPPClient::XMPPClient(const QString &server)
{
    m_client = new Client(server.toStdString());
    m_client->registerConnectionListener(this);
}

XMPPClient::~XMPPClient(void)
{
    disconnect();
    if (m_client != 0)
        delete m_client;
}

void XMPPClient::connect(void)
{
    qDebug() << "connect";
    bool connected = m_client->connect(false);
    if (connected) m_recvTimer = startTimer(100);
}
void XMPPClient::disconnect(void)
{
    qDebug() << "disconneect";
    m_client->disconnect();
}
bool XMPPClient::authed() const
{
    if (m_client == 0) return false;
    return m_client->authed();
}
ConnectionState XMPPClient::state() const
{
    if (m_client == 0) return StateDisconnected;
    return m_client->state();
}
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
void XMPPClient::setHTTPProxy(const QString &host, int port, const QString &user, const QString &pass)
{
    const std::string& xmppHost = m_client->server();
    int xmppPort = m_client->port();

    ConnectionTCPClient* conn0 = new ConnectionTCPClient( m_client->logInstance(), host.toStdString(), port );
    ConnectionHTTPProxy* conn1 = new ConnectionHTTPProxy( m_client, conn0, m_client->logInstance(), xmppHost, xmppPort );

    conn1->setProxyAuth(user.toStdString(), pass.toStdString());
    m_client->setConnectionImpl( conn1 );
}
void XMPPClient::setSOCKS5Proxy(const QString &host, int port, const QString &user, const QString &pass)
{
    const std::string& xmppHost = m_client->server();
    int xmppPort = m_client->port();

    ConnectionTCPClient* conn0 = new ConnectionTCPClient( m_client->logInstance(), host.toStdString(), port );
    ConnectionSOCKS5Proxy* conn1 = new ConnectionSOCKS5Proxy( m_client, conn0, m_client->logInstance(), xmppHost, xmppPort );

    conn1->setProxyAuth(user.toStdString(), pass.toStdString());
    m_client->setConnectionImpl( conn1 );
}

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
