/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef JCLIENT_H
#define JCLIENT_H

#include <gloox/presence.h>
#include <gloox/presencehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/client.h>
#include <gloox/jid.h>

#include <QString>

using namespace gloox;

//class JID;
//class QString;

class JClient : public PresenceHandler, ConnectionListener
{
public:
    JClient();

    virtual void handlePresence(const Presence& presence );
    virtual void onConnect();
    virtual void onDisconnect( ConnectionError e );
    virtual bool onTLSConnect( const CertInfo& info );

    void connect(JID &jid, const QString &password);

private:
    Client *client;
};

#endif // JCLIENT_H
