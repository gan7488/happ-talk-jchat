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
class QSvgWidget;

/**
 * @brief Login dialog.
 */
class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);

    /**
     * @brief Get username.
     */
    const QString username() const { return uname->text(); }
    /**
     * @brief Get server.
     */
    const QString server() const { return serv->text(); }
    /**
     * @brief Get password.
     */
    const QString password() const { return pass->text(); }

protected:
    /**
     * @brief Show event.
     */
    void showEvent(QShowEvent *e);

private slots:
    /**
     * @brief Accept button pressed.
     */
    void accepted();
    /**
     * @brief Reject button pressed.
     */
    void rejected();

    /**
     * @brief Connection is established.
     */
    void connected();
    /**
     * @brief The connection was aborted.
     * @param e The reason for the disconnection.
     */
    void disconnected(ConnectionError e);
    /**
     * @brief Registration completed.
     */
    void registrationCompleted(RegistrationResult result);

private:
    /**
     * @brief Creating widgets.
     */
    void createElements();
    /**
     * @brief Layout widgets.
     */
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
