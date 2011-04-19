/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "xmppregistration.h"
#include <QDebug>

/*
 Constructor and destructor
 */
XMPPRegistration::XMPPRegistration(const QString &server)
    : XMPPClient(server)
{
    m_client->disableRoster();

    m_reg = new Registration(m_client);
    m_reg->registerRegistrationHandler(this);
}

XMPPRegistration::~XMPPRegistration()
{
    delete m_reg;
}

/*
 Managing
 */
void XMPPRegistration::createAccount()
{
    if (state() == StateDisconnected) return;
    m_reg->fetchRegistrationFields();
    qDebug() << "create account";
}
/*
void XMPPRegistration::changePassword()
{
    if (state() == StateDisconnected) return;
    m_reg->changePassword(m_username.toStdString(), m_password.toStdString());
    qDebug() << "change password";
}

void XMPPRegistration::removeAccount()
{
    if (state() == StateDisconnected) return;
    m_reg->removeAccount();
    qDebug() << "remove account";
}
*/
/*
 RegistrationHandler methods goes here.
 */
void XMPPRegistration::handleRegistrationFields (const JID &, int fields, std::string)
{
    qDebug() << "registration fields";
    RegistrationFields vals;
    vals.username = m_username.toStdString();
    vals.password = m_password.toStdString();
    m_reg->createAccount( fields, vals );
}

void XMPPRegistration::handleAlreadyRegistered (const JID & from)
{
    qDebug() << "alreadyRegistered";
    emit accountAlreadyRegistered(from);
}

void XMPPRegistration::handleRegistrationResult (const JID &, RegistrationResult regResult)
{
    emit registrationCompleted(regResult);
}

void XMPPRegistration::handleDataForm (const JID &, const DataForm &)
{
    qDebug() << "dataForm recieved";
}

void XMPPRegistration::handleOOB (const JID &, const OOB &)
{
    qDebug() << "OOD recieved";
}
