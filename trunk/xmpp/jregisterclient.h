/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef JREGISTERCLIENT_H
#define JREGISTERCLIENT_H

#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/registration.h>

#include <QObject>
#include <QString>

using namespace gloox;

class JRegisterClient : public QObject, ConnectionListener, RegistrationHandler
{
    Q_OBJECT
public:
    explicit JRegisterClient(QObject *parent = 0);

    virtual void onConnect();
    virtual void onDisconnect( ConnectionError e );
    virtual bool onTLSConnect( const CertInfo& info );

    virtual void handleRegistrationFields( const JID& /*from*/, int fields, std::string instructions );
    virtual void handleRegistrationResult( const JID& /*from*/, RegistrationResult result );
    virtual void handleAlreadyRegistered( const JID& /*from*/ );
    virtual void handleDataForm( const JID& /*from*/, const DataForm& /*form*/ );
    virtual void handleOOB( const JID& /*from*/, const OOB& oob );

    void createAccount(const QString& server);

    QString username() const { return m_username; }
    QString password() const { return m_password; }
    void setUsername(const QString &name) { m_username = name; }
    void setPassword(const QString &pas) { m_password = pas; }
signals:

public slots:

private:
    QString m_username;
    QString m_password;
    Registration *reg;
    Client *client;
};

#endif // JREGISTERCLIENT_H
