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

/**
 * @brief This class implemets jabber registration.
 * @example How to use:
 *   1)  connect()
 *   2)  set username and password
 *   3)  when connection established call createAccount()
 *   4)  when registration completed call disconnect()
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

    /**
     * @brief Get acccount username.
     */
    QString username() const { return m_username; }
    /**
     * @brief Get account password.
     */
    QString password() const { return m_password; }
    /**
     * @brief Set acccount username.
     */
    void setUsername(const QString &vl) { m_username = vl; }
    /**
     * @brief Set account password.
     */
    void setPassword(const QString &vl) { m_password = vl; }

public slots:
    /**
     * @brief Create new account
     * @example How to use:
     *   connect connected() with one of this functions
     */
    void createAccount();

signals:
    /**
     * @brief Signal is raises at the completion of the registration.
     */
    void registrationCompleted(RegistrationResult);
    /**
     * @brief Signal is raised if such an account already exists
     * @param from This JID already existed.
     */
    void accountAlreadyRegistered(const JID& from);

protected:
    /**
     * @brief Overrides of gloox::RegistrationHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleRegistrationFields (const JID &from, int fields, std::string instructions);
    /**
     * @brief Overrides of gloox::RegistrationHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleAlreadyRegistered (const JID &from);
    /**
     * @brief Overrides of gloox::RegistrationHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleRegistrationResult (const JID &from, RegistrationResult regResult);
    /**
     * @brief Overrides of gloox::RegistrationHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleDataForm (const JID &from, const DataForm &form);
    /**
     * @brief Overrides of gloox::RegistrationHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
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
