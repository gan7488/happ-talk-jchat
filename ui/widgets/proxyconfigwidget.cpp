/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "proxyconfigwidget.h"
#include <QtGui>
#include <QSvgWidget>

/*
 Constructors
 */
ProxyConfigWidget::ProxyConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWhatsThis(tr("Proxy settings.<br>"
                          "You can choose one of the options:"
                          "<ul><li>none - no proxy;</li>"
                          "<li>http proxy;</li>"
                          "<li>socks5 proxy.</li></ul>"
                          "and specify the proxy settings"));

    createElements();
    layoutElements();
}

/*
 Setup UI
 */
void ProxyConfigWidget::createElements()
{
    proxyType = new QComboBox();
    proxyType->addItem(QIcon(":/images/server.svg"), tr("None"));
    proxyType->addItem(QIcon(":/images/web.svg"), tr("HTTP Proxy"));
    proxyType->addItem(QIcon(":/images/network.svg"), tr("SOCKS 5 Proxy"));
    proxyType->setToolTip(tr("Select proxy type"));

    connect(proxyType, SIGNAL(currentIndexChanged(int)), this, SLOT(proxyTypeChanged(int)));

    proxyHost = new QLineEdit();
    proxyHost->setMaxLength(30);
    proxyHost->setToolTip(tr("Proxy host type here"));
    proxyPort = new QLineEdit();
    proxyPort->setMaxLength(6);
    proxyPort->setToolTip(tr("Proxy port type here"));
    proxyPort->setInputMask("000000");
    proxyUser = new QLineEdit();
    proxyUser->setToolTip(tr("User name for proxy type here"));
    proxyUser->setMaxLength(30);
    proxyPass = new QLineEdit();
    proxyPass->setMaxLength(30);
    proxyPass->setToolTip(tr("Password for proxy type here"));
    proxyPass->setEchoMode(QLineEdit::PasswordEchoOnEdit);
}
void ProxyConfigWidget::layoutElements()
{
    QFormLayout *fLayout = new QFormLayout();
    fLayout->addRow(tr("Proxy type:"), proxyType);
    fLayout->addRow(tr("Proxy host:"), proxyHost);
    fLayout->addRow(tr("Proxy port:"), proxyPort);
    fLayout->addRow(tr("Username:"), proxyUser);
    fLayout->addRow(tr("Password:"), proxyPass);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addLayout(fLayout);
    hLayout->addStretch();

    QSvgWidget *pic = new QSvgWidget(":/images/web.svg");
    pic->setFixedSize(100,100);

    hLayout->addWidget(pic);
    this->setLayout(hLayout);
}

/*
 Slots
 */
void ProxyConfigWidget::load()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       qApp->organizationName(), qApp->applicationName());

    QString proxy = settings.value("proxy/type", "none").toString().toLower();

    if (proxy == "http")        proxyType->setCurrentIndex(1);
    else if (proxy == "socks5") proxyType->setCurrentIndex(2);
    else if (proxy == "none")
    {
        proxyType->setCurrentIndex(0);
        proxyTypeChanged(0);
    }

    proxyHost->setText(settings.value("proxy/host").toString());
    proxyPort->setText(settings.value("proxy/port").toString());
    proxyUser->setText(settings.value("proxy/user").toString());
    proxyPass->setText(settings.value("proxy/pass").toString());
}

void ProxyConfigWidget::save()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       qApp->organizationName(), qApp->applicationName());

    switch (proxyType->currentIndex())
    {
    case 0:
        settings.setValue("proxy/type", "none");
        break;
    case 1:
        settings.setValue("proxy/type", "http");
        break;
    case 2:
        settings.setValue("proxy/type", "socks5");
        break;
    }

    settings.setValue("proxy/host", proxyHost->text());
    settings.setValue("proxy/port", proxyPort->text());
    settings.setValue("proxy/user", proxyUser->text());
    settings.setValue("proxy/pass", proxyPass->text());
}

void ProxyConfigWidget::proxyTypeChanged(int index)
{
    if (index == 0)
    {
        proxyHost->setEnabled(false);
        proxyPort->setEnabled(false);
        proxyUser->setEnabled(false);
        proxyPass->setEnabled(false);
    }
    else
    {
        proxyHost->setEnabled(true);
        proxyPort->setEnabled(true);
        proxyUser->setEnabled(true);
        proxyPass->setEnabled(true);
    }
}
