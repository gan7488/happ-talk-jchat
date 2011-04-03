/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "xmpp/xmppregistration.h"

class QCheckBox;
class QDialogButtonBox;
class QLineEdit;
class QSvgWidget;

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);

    const QString username() const;
    const QString server() const;
    const QString password() const;

protected:
    void showEvent(QShowEvent *e);

private:
    void createElements();
    void layoutElements();

    QLineEdit *uname;
    QLineEdit *serv;
    QLineEdit *pass;

    QCheckBox *join;

    QSvgWidget *logo;

    QDialogButtonBox *buttons;

    XMPPRegistration *reg;
private slots:
    void accepted();
    void rejected();

    void connected();
    void disconnected(ConnectionError e);
    void registrationCompleted(RegistrationResult);

};

#endif // LOGINDIALOG_H
