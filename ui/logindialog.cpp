/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "logindialog.h"
#include "consts.h"
#include <QtGui>
#include <QSvgWidget>
#include "xmpp/xmppregistration.h"

/*
 Constructors
 */
LoginDialog::LoginDialog(QWidget *parent) :
        QDialog(parent), reg(0)
{
    this->setWindowTitle(tr("Login"));
    this->setWindowIcon(QIcon(":/images/lock.svg"));

    createElements();
    layoutElements();

    this->setFixedSize(sizeHint());
}

/*
 Events
 */
void LoginDialog::showEvent(QShowEvent *e)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, org, app);
    uname->setText(settings.value("account/username").toString());
    serv->setText(settings.value("account/server").toString());

    QDialog::showEvent(e);
}

/*
 Setup UI
 */
void LoginDialog::createElements()
{
    uname   = new QLineEdit();
    serv    = new QLineEdit();
    pass    = new QLineEdit();
    pass->setEchoMode(QLineEdit::PasswordEchoOnEdit);

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

/*
 Slots
 */
void LoginDialog::accepted()
{
    // Just connect, not register
    if (join->checkState() != Qt::Checked)
    {
        // Checking all fields
        if (uname->text().isEmpty() || serv->text().isEmpty() || pass->text().isEmpty())
        {
            QMessageBox::information(this,
                                     tr("Some fields is empty!"),
                                     tr("Fill all fields (username, server, password)"), QMessageBox::Ok);
            return;
        }
        // Save information
        QSettings settings(QSettings::IniFormat, QSettings::UserScope, org, app);
        settings.setValue("account/username", uname->text());
        settings.setValue("account/server", serv->text());

        // Accept
        this->accept();
        return;
    }
    qDebug() << "join";

    // Checking server field
    if (serv->text().isEmpty())
    {
        QMessageBox::information(this,
                                 tr("Where?"),
                                 tr("Type server name"), QMessageBox::Ok);
        return;
    }

    // Registration
    if (reg) delete reg;
    reg = new XMPPRegistration(server());

    // Load proxy settings
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       qApp->organizationName(), qApp->applicationName());

    QString proxy = settings.value("proxy/type", "none").toString().toLower();
    int port = settings.value("proxy/port", "-1").toInt();

    if (proxy == "socks5")
        reg->setSOCKS5Proxy(settings.value("proxy/host").toString(), port,
                            settings.value("proxy/user").toString(),
                            settings.value("proxy/pass").toString());
    else if (proxy == "http")
        reg->setHTTPProxy(settings.value("proxy/host").toString(), port,
                            settings.value("proxy/user").toString(),
                            settings.value("proxy/pass").toString());

    // Fill username an password
    reg->setUsername(username());
    reg->setPassword(password());

    // Connecting signals - slots
    connect(reg, SIGNAL(connected()), this, SLOT(connected()));
    connect(reg, SIGNAL(disconnected(ConnectionError)),
            this, SLOT(disconnected(ConnectionError)));
    connect(reg,SIGNAL(registrationCompleted(RegistrationResult)),
            this, SLOT(registrationCompleted(RegistrationResult)));

    // Connecting && registration goes here
    // Registration occurs when a connection is established
    reg->connect();
}

void LoginDialog::rejected()
{
    this->reject();
}

void LoginDialog::connected()
{
    // Registration occurs when a connection is established
    // It means here
    reg->createAccount();
}

void LoginDialog::disconnected(ConnectionError e)
{
    if (e != ConnUserDisconnected)
        QMessageBox::information(this, tr("Some troubles here!"), tr("Disconnected"));
}

void LoginDialog::registrationCompleted(RegistrationResult r)
{
    reg->disconnect();
    if (r == RegistrationSuccess)
    {
        QMessageBox::information(this, tr("Success!"), tr("Registration succesfully completed"));
        join->setChecked(false);
    }
    else
        QMessageBox::information(this, tr("Failed!"), tr("Registration has not completed"));
}

