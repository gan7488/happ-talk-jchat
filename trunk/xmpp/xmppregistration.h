/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPREGISTRATION_H
#define XMPPREGISTRATION_H

#include <QObject>
#include <gloox/registration.h>
#include <gloox/registrationhandler.h>
#include "xmppclient.h"

using namespace gloox;

class XMPPRegistration : public XMPPClient, RegistrationHandler
{
    Q_OBJECT
public:
    XMPPRegistration(const QString& server);
    virtual ~XMPPRegistration();

    QString username() const { return m_username; }
    QString password() const { return m_password; }
    void setUsername(const QString &vl) { m_username = vl; }
    void setPassword(const QString &vl) { m_password = vl; }

public slots:
    void createAccount();
    void changePassword();
    void removeAccount();

signals:
    void registrationCompleted(RegistrationResult);

protected:
    /*  Overrides of gloox::RegistrationHandler  */
    virtual void handleRegistrationFields (const JID &from, int fields, std::string instructions);
    virtual void handleAlreadyRegistered (const JID &from);
    virtual void handleRegistrationResult (const JID &from, RegistrationResult regResult);
    virtual void handleDataForm (const JID &from, const DataForm &form);
    virtual void handleOOB (const JID &from, const OOB &oob);

private:
    QString m_username;
    QString m_password;

    Registration *m_reg;
};

#endif // XMPPREGISTRATION_H
