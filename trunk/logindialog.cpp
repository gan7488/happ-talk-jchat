/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "logindialog.h"
#include <QtGui>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setFixedSize(250, 105);
    this->setWindowTitle(tr("Login"));
    createElements();
    layoutElements();
}

void LoginDialog::createElements()
{
    noteAcc = new QLabel(tr("Account:"));
    notePas = new QLabel(tr("Password:"));

    account = new QTextEdit();
    account->setFixedHeight(25);
    password = new QTextEdit();
    password->setFixedHeight(25);

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("Login"), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("Cancel"), QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("Join"), QDialogButtonBox::HelpRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
    connect(buttonBox, SIGNAL(helpRequested()), this, SLOT(join()));
}

void LoginDialog::layoutElements()
{
    QFormLayout *fLayout = new QFormLayout();
    fLayout->addRow(noteAcc, account);
    fLayout->addRow(notePas, password);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addStretch(5);
    vLayout->addWidget(buttonBox);

    fLayout->addRow(vLayout);
    this->setLayout(fLayout);
}

void LoginDialog::accepted()
{
    this->accept();
}

void LoginDialog::rejected()
{
    this->reject();
}

void LoginDialog::join()
{
    QMessageBox::information(this, "REGISTER FROM!", "DO IT", QMessageBox::Ok, QMessageBox::Cancel);
}

QString LoginDialog::getAccount() const
{
    return account->toPlainText();
}
QString LoginDialog::getPassword() const
{
    return password->toPlainText();
}

