/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class QTextEdit;
class QLabel;
class QDialogButtonBox;

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);

signals:

public slots:

private:
    void createElements();
    void layoutElements();

    QTextEdit *account;
    QTextEdit *password;

    QLabel *noteAcc;
    QLabel *notePas;

    QDialogButtonBox *buttonBox;

private slots:
    void accepted();
    void rejected();
    void join();
};

#endif // LOGINDIALOG_H
