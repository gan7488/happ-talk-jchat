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

/*
 This class implements connection functions.
 How to use:
    1) call connect()
    2) working
    3) call disconnect()
 */
class XMPPClient : public QObject,
                          ConnectionListener
{
    Q_OBJECT
public:
    /*
     Constructors and destructor.
     */
    XMPPClient(const JID& jid, const QString& password, int port = -1);
    XMPPClient(const QString& server);
    virtual ~XMPPClient(void);

    /*
     Connection functions.
     */
    void connect(void);
    void disconnect(void);

    /*
     Connection status.
     */
    bool authed() const;
    ConnectionState state() const;

    /*
     Attach or detach client extensions.
     */
    void attach(XMPPClientExtension* ext);
    void detach(XMPPClientExtension* ext);
    void operator+=(XMPPClientExtension *ext) { attach(ext); }
    void operator-=(XMPPClientExtension *ext) { detach(ext); }

    /*
     Proxies settings goes here.
     */
    void setHTTPProxy(const QString& host, int port, const QString& user, const QString& pass);
    void setSOCKS5Proxy(const QString& host, int port, const QString& user, const QString& pass);

    /*
     Roster manager
     */
    RosterManager* roster() const { return m_client->rosterManager(); }
signals:
    /*
     Occurs when connection established.
     */
    void connected();
    /*
     Occurs when connection was disconnected.
     */
    void disconnected(ConnectionError e);

protected:
    /*
     Overrides of gloox::ConnectionListener
     */
    virtual void onConnect();
    virtual void onDisconnect( ConnectionError e );
    virtual bool onTLSConnect( const CertInfo& info );

private:
    /*
     Top Secret!
     */
    void timerEvent(QTimerEvent */*event*/) { m_client->recv(0); }
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
