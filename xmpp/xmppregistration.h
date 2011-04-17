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

/*
 This class implemets jabber registration.
 How to use:
    1)  connect()
    2)  set username and password
    3)  when connection established call createAccount()
    4)  when registration completed call disconnect()
 Change password and remove account POSSIBLE DON'T WORK.
 */
class XMPPRegistration : public XMPPClient,
                                RegistrationHandler
{
    Q_OBJECT
public:
    /*
     Constructor and destructor
     */
    XMPPRegistration(const QString& server);
    virtual ~XMPPRegistration();

    /*
     Setters and getters
     */
    QString username() const { return m_username; }
    QString password() const { return m_password; }
    void setUsername(const QString &vl) { m_username = vl; }
    void setPassword(const QString &vl) { m_password = vl; }

public slots:
    /*
     Managing. Why slots?
     How to use (example):
        connect connected() with one of this functions
     */
    void createAccount();
    void changePassword();
    void removeAccount();

signals:
    /*
     Registration completed.
     */
    void registrationCompleted(RegistrationResult);
    /*
     Already existed
     */
    void accountAlreadyRegistered(const JID& from);

protected:
    /*
     Overrides of gloox::RegistrationHandler
    */
    virtual void handleRegistrationFields (const JID &from, int fields, std::string instructions);
    virtual void handleAlreadyRegistered (const JID &from);
    virtual void handleRegistrationResult (const JID &from, RegistrationResult regResult);
    virtual void handleDataForm (const JID &from, const DataForm &form);
    virtual void handleOOB (const JID &from, const OOB &oob);

private:
    /*
     Private fields.
     */
    QString m_username;
    QString m_password;

    Registration *m_reg;
};

#endif // XMPPREGISTRATION_H
