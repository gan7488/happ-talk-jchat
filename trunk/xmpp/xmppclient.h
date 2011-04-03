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

class XMPPClient : public QObject, ConnectionListener
{
    Q_OBJECT
public:
    XMPPClient(const JID& jid, const QString& password, int port = -1);
    XMPPClient(const QString& server);
    virtual ~XMPPClient(void);

    void connect(void);
    void disconnect(void);

    bool authed() const;
    ConnectionState state() const;

    void attach(XMPPClientExtension* ext);
    void detach(XMPPClientExtension* ext);

    void setHTTPProxy(const QString& host, int port, const QString& user, const QString& pass);
    void setSOCKS5Proxy(const QString& host, int port, const QString& user, const QString& pass);

signals:
    void connected();
    void disconnected(ConnectionError e);

public slots:

protected:
    /*  Overrides of gloox::ConnectionListener  */
    virtual void onConnect();
    virtual void onDisconnect( ConnectionError e );
    virtual bool onTLSConnect( const CertInfo& info );

    Client  *m_client;
    QList<XMPPClientExtension *> m_extensions;

private:
    void timerEvent(QTimerEvent */*event*/) { m_client->recv(0); }

    int m_recvTimer;
};

#endif // XMPPCLIENT_H
