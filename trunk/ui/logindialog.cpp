/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "logindialog.h"
#include <QtGui>
#include "xmpp/jregisterclient.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setFixedSize(350, 105);
    this->setWindowTitle(tr("Login"));
    this->setWindowIcon(QIcon(":/images/lock.svg"));

    createElements();
    layoutElements();
}

void LoginDialog::createElements()
{
    noteAcc = new QLabel(tr("Account:"));
    notePas = new QLabel(tr("Password:"));

    account = new QLineEdit();
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("Login"), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("Cancel"), QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("Join"), QDialogButtonBox::HelpRole);
    buttonBox->setCenterButtons(true);

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
    vLayout->addLayout(fLayout);
    vLayout->addStretch(5);
    vLayout->addWidget(buttonBox);

    this->setLayout(vLayout);
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
    qDebug() << "join";
    JRegisterClient reg;
    reg.createAccount("jabber.uruchie.org");
}

QString LoginDialog::getAccount() const
{
    return account->text();
}
QString LoginDialog::getPassword() const
{
    return password->text();
}

