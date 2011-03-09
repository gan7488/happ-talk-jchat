/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class QLineEdit;
class QLabel;
class QDialogButtonBox;

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);

    QString getAccount() const;
    QString getPassword() const;

signals:

public slots:

private:
    void createElements();
    void layoutElements();

    QLineEdit *account;
    QLineEdit *password;

    QLabel *noteAcc;
    QLabel *notePas;

    QDialogButtonBox *buttonBox;

private slots:
    void accepted();
    void rejected();
    void join();
};

#endif // LOGINDIALOG_H