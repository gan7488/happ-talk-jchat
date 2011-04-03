/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "logindialog.h"
#include "consts.h"
#include <QtGui>
#include <QSvgWidget>
#include "xmpp/jregisterclient.h"
#include "xmpp/xmppregistration.h"

LoginDialog::LoginDialog(QWidget *parent) :
        QDialog(parent), reg(0)
{
    //this->setFixedSize(310, 215);
    //this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setWindowTitle(tr("Login"));
    this->setWindowIcon(QIcon(":/images/lock.svg"));

    createElements();
    layoutElements();

    this->setFixedSize(sizeHint());
}

void LoginDialog::showEvent(QShowEvent *e)
{
    QSettings settings(QSettings::IniFormat, QSettings::SystemScope, org, app);
    uname->setText(settings.value("account/username").toString());
    serv->setText(settings.value("account/server").toString());

    QDialog::showEvent(e);
}

void LoginDialog::createElements()
{
    uname   = new QLineEdit();
    serv    = new QLineEdit();
    pass    = new QLineEdit();
    pass->setEchoMode(QLineEdit::Password);

    join = new QCheckBox(tr("Create account"));

    buttons = new QDialogButtonBox();
    buttons->addButton(tr("Login"), QDialogButtonBox::AcceptRole);
    buttons->addButton(tr("Cancel"), QDialogButtonBox::RejectRole);
    buttons->setCenterButtons(true);

    connect(buttons, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(rejected()));

    logo = new QSvgWidget();
    logo->setFixedSize(150,150);
    logo->load(QString(":/images/lock.svg"));
}

void LoginDialog::layoutElements()
{
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(new QLabel(tr("Username:")));
    vLayout->addWidget(uname);
    vLayout->addWidget(new QLabel(tr("Server:")));
    vLayout->addWidget(serv);
    vLayout->addWidget(new QLabel(tr("Password:")));
    vLayout->addWidget(pass);
    vLayout->addWidget(join);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(logo);
    hLayout->addLayout(vLayout);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(hLayout);
    layout->addSpacing(10);
    layout->addWidget(buttons);

    this->setLayout(layout);
}

void LoginDialog::accepted()
{
    if (join->checkState() != Qt::Checked)
    {
        if (uname->text().isEmpty() || serv->text().isEmpty() || pass->text().isEmpty())
        {
            QMessageBox::information(this,
                                     tr("Some fields is empty!"),
                                     tr("Fill all fields (username, server, password)"), QMessageBox::Ok);
            return;
        }
        QSettings settings(QSettings::IniFormat, QSettings::SystemScope, org, app);
        settings.setValue("account/username", uname->text());
        settings.setValue("account/server", serv->text());

        this->accept();
        return;
    }
    //@todo complete
    qDebug() << "join";
    if (serv->text().isEmpty())
    {
        QMessageBox::information(this,
                                 tr("Where?"),
                                 tr("Type server name"), QMessageBox::Ok);
        return;
    }
    //JRegisterClient reg;
    //reg.createAccount("jabber.uruchie.org");
    reg = new XMPPRegistration(server());
    reg->setUsername(username());
    reg->setPassword(password());
    reg->connect();
    connect(reg, SIGNAL(connected()), this, SLOT(connected()));
    connect(reg,SIGNAL(registrationCompleted(RegistrationResult)),
            this, SLOT(registrationCompleted(RegistrationResult)));
}

void LoginDialog::rejected()
{
    this->reject();
}

const QString LoginDialog::username() const
{
    return uname->text();
}
const QString LoginDialog::server() const
{
    return serv->text();
}
const QString LoginDialog::password() const
{
    return pass->text();
}

void LoginDialog::connected()
{
    reg->createAccount();
}

void LoginDialog::disconnected(ConnectionError e)
{

}

void LoginDialog::registrationCompleted(RegistrationResult r)
{
    reg->disconnect();
    if (r == RegistrationSuccess)
    {
        QMessageBox::information(this, tr("SUCCESS!"), tr("Registration succesfully completed"));
        join->setChecked(false);
    }
    else
        QMessageBox::information(this, tr("Failed!"), tr("Registration has not completed"));
}

