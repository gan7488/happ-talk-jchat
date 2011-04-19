/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "xmpp/xmppregistration.h"

class QCheckBox;
class QDialogButtonBox;
//class QLineEdit;
class QSvgWidget;

/*
 Login dialog
 */
class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);

    /*
     Getters
     */
    const QString username() const { return uname->text(); }
    const QString server() const { return serv->text(); }
    const QString password() const { return pass->text(); }

protected:
    /*
     Events
     */
    void showEvent(QShowEvent *e);

private slots:
    /*
     Slots
     */
    void accepted();
    void rejected();

    void connected();
    void disconnected(ConnectionError e);
    void registrationCompleted(RegistrationResult);

private:
    /*
     Setup UI
     */
    void createElements();
    void layoutElements();

    /*
     Elements
     */
    QLineEdit *uname;
    QLineEdit *serv;
    QLineEdit *pass;

    QCheckBox *join;

    QSvgWidget *logo;

    QDialogButtonBox *buttons;

    XMPPRegistration *reg;
};

#endif // LOGINDIALOG_H
