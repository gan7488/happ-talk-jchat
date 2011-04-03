/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "configdialog.h"
#include "widgets/generalconfigwidget.h"
#include "widgets/chatconfigwidget.h"
#include "widgets/proxyconfigwidget.h"
#include <QtGui>

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setMinimumSize(500, 400);
    this->setWindowTitle(tr("Configuration"));
    this->setWindowIcon(QIcon(":/images/preferences.svg"));

    createButtons();
    createTabs();
    layoutElements();
}

void ConfigDialog::createButtons()
{
    QPushButton *apply;

    buttons = new QDialogButtonBox();
    buttons->addButton(tr("OK"), QDialogButtonBox::AcceptRole);
    buttons->addButton(tr("Cancel"), QDialogButtonBox::RejectRole);
    apply = buttons->addButton(tr("Apply"), QDialogButtonBox::ApplyRole);

    connect(buttons, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(rejected()));
    connect(apply, SIGNAL(clicked()), this, SLOT(applied()));
}


void ConfigDialog::createTabs()
{
    tabs = new QTabWidget();
    tabs->setIconSize(QSize(40,40));

    //TODO
    generalConf = new GeneralConfigWidget();
    chatConf = new ChatConfigWidget();
    proxyConf = new ProxyConfigWidget();

    int tab;
    tab = tabs->addTab(generalConf, QIcon(":/images/desktop.svg"), tr("General"));
    tabs->setTabToolTip(tab, tr("General configuration"));
    tabs->setTabWhatsThis(tab, tr("It's general configuration!"));

    tab = tabs->addTab(chatConf,QIcon(":/images/users.svg"), tr("Chat"));
    tabs->setTabToolTip(tab, tr("Chat configuration"));
    tabs->setTabWhatsThis(tab, tr("It's chat configuration!"));

    tab = tabs->addTab(proxyConf, QIcon(":/images/web.svg"), tr("Proxy"));
    tabs->setTabToolTip(tab, tr("Proxy configuration"));
    tabs->setTabWhatsThis(tab, tr("It's general configuration!"));

    //tab = tabs->addTab(new QLabel("TRANSFER SETTINGS GOES HERE"), QIcon(":/images/transfer.svg"), tr("Transfer"));
    //tabs->setTabToolTip(tab, tr("General configuration"));
    //tabs->setTabWhatsThis(tab, tr("It's general configuration!"));

}


void ConfigDialog::layoutElements()
{
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(tabs);
    vLayout->addSpacing(10);
    vLayout->addWidget(buttons);

    this->setLayout(vLayout);
}

void ConfigDialog::accepted()
{
    //TODO save & apply
    accept();
}

void ConfigDialog::applied()
{
    //TODO apply
}

void ConfigDialog::rejected()
{
    //TODO reject
    reject();
}
