/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "jclient.h"
#include <QMessageBox>

JClient::JClient()
{

}

void JClient::handlePresence(const Presence &presence)
{
    QMessageBox msgBox;
    msgBox.setText("void JClient::handlePresence(const Presence &presence)");
    QString str = "Id: %1  \nFrom: %2\nTo: %3";
    msgBox.setInformativeText(str.arg(QString::fromStdString(presence.id()),
                                      QString::fromStdString(presence.from().bare()),
                                      QString::fromStdString(presence.to().bare())));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}

void JClient::onConnect()
{
    QMessageBox msgBox;
    msgBox.setText("void JClient::onConnect()");
    msgBox.setStandardButtons(QMessageBox::Ok);
    int ret = msgBox.exec();
}
void JClient::onDisconnect( ConnectionError e )
{
    QMessageBox msgBox;
    //msgBox.setText("void JClient::onDisconnect( ConnectionError e )");
    msgBox.setText(QString("Error %1").arg((int)e));
    msgBox.setStandardButtons(QMessageBox::Ok);
    int ret = msgBox.exec();
}

bool JClient::onTLSConnect( const CertInfo& info )
{
    QMessageBox msgBox;
    msgBox.setText("bool JClient::onTLSConnect( const CertInfo& info )");
    msgBox.setStandardButtons(QMessageBox::Ok);
    int ret = msgBox.exec();
}

void JClient::connect(JID &jid, const QString &password)
{
    client = new Client(jid, password.toStdString());
    client->registerConnectionListener( this );
    client->registerPresenceHandler( this );
    client->connect();
}
