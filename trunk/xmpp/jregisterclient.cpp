/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "jregisterclient.h"
#include <QtDebug>

JRegisterClient::JRegisterClient(QObject *parent) :
    QObject(parent)
{
}

void JRegisterClient::onConnect()
{
    qDebug() << "registration connect";
    reg->fetchRegistrationFields();
}
void JRegisterClient::onDisconnect( ConnectionError e )
{
    qDebug() << "register disconnect";
}

bool JRegisterClient::onTLSConnect( const CertInfo& info )
{
    qDebug() << "register tls connect";
    return true;
}

void JRegisterClient::handleRegistrationFields( const JID& /*from*/, int fields, std::string instructions )
{
    qDebug() << "handle registration fields " << fields << " instructions " << instructions.c_str();
    RegistrationFields vals;
    vals.username = "jchat";
    vals.password = "test";
    reg->createAccount( fields, vals );
}

void JRegisterClient::handleRegistrationResult( const JID& /*from*/, RegistrationResult result )
{
    qDebug() << "registration result is " << result;
    client->disconnect();
}

void JRegisterClient::handleAlreadyRegistered( const JID& /*from*/ )
{
    qDebug() << "username already registered";
}

void JRegisterClient::handleDataForm( const JID& /*from*/, const DataForm& /*form*/ )
{
    qDebug() << "register data form received";
}

void JRegisterClient::handleOOB( const JID& /*from*/, const OOB& oob )
{
    qDebug() << "register oob requested url " << oob.url().c_str() << " descr " << oob.desc().c_str();
}

void JRegisterClient::createAccount(const QString& server)
{
    client = new Client(server.toStdString());
    client->disableRoster();
    client->registerConnectionListener(this);

    reg = new Registration(client);
    reg->registerRegistrationHandler(this);

    client->connect();

     delete reg;
    delete client;

}
