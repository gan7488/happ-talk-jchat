/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "proxyconfigwidget.h"
#include <QtGui>
#include <QSvgWidget>

ProxyConfigWidget::ProxyConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    createElements();
    layoutElements();
}
void ProxyConfigWidget::createElements()
{
    proxyType = new QComboBox();
    proxyType->addItem(QIcon(":/images/server.svg"), tr("None"));
    proxyType->addItem(QIcon(":/images/web.svg"), tr("HTTP Proxy"));
    proxyType->addItem(QIcon(":/images/network.svg"), tr("SOCKS 5 Proxy"));
    connect(proxyType, SIGNAL(currentIndexChanged(int)), this, SLOT(proxyTypeChanged(int)));

    proxyHost = new QLineEdit();
    proxyHost->setMaxLength(30);
    proxyPort = new QLineEdit();
    proxyPort->setMaxLength(6);
    proxyUser = new QLineEdit();
    proxyUser->setMaxLength(30);
    proxyPass = new QLineEdit();
    proxyPass->setMaxLength(30);

    proxyConf = new QFormLayout();
    proxyConf->addRow(tr("Proxy type:"), proxyType);
    proxyConf->addRow(tr("Proxy host:"), proxyHost);
    proxyConf->addRow(tr("Proxy port:"), proxyPort);
    proxyConf->addRow(tr("Username:"), proxyUser);
    proxyConf->addRow(tr("Password:"), proxyPass);

    pic = new QSvgWidget(":/images/web.svg");
    pic->setFixedSize(100,100);
}
void ProxyConfigWidget::layoutElements()
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addLayout(proxyConf);
    hLayout->addStretch();
    hLayout->addWidget(pic);
    this->setLayout(hLayout);
}
void ProxyConfigWidget::load()
{
    //QSettings settings(QSettings::IniFormat, QSettings::SystemScope, org, app);
   // settings.setValue("maindialog/geometry", saveGeometry())
}

void ProxyConfigWidget::save()
{
    //QSettings settings(QSettings::IniFormat, QSettings::SystemScope, org, app);
    //settings.setValue("maindialog/geometry", saveGeometry());
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
