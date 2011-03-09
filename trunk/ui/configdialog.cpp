/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "configdialog.h"
#include "generalconfigwidget.h"
#include "chatconfigwidget.h"
#include "proxyconfigwidget.h"
#include <QtGui>

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setMinimumSize(500, 400);
    this->setWindowTitle(tr("Configuration"));
    createTabs();
    createButtons();
    layoutElements();
}

void ConfigDialog::createTabs()
{
    tabs = new QTabWidget();

    //TODO
    generalConf = new GeneralConfigWidget();
    chatConf = new ChatConfigWidget();
    proxyConf = new ProxyConfigWidget();

    tabs->addTab(generalConf, tr("General"));
    tabs->addTab(chatConf, tr("Chat"));
    tabs->addTab(proxyConf, tr("Proxy"));
}

void ConfigDialog::createButtons()
{
    QPushButton *apply;

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("OK"), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("Cancel"), QDialogButtonBox::RejectRole);
    apply = buttonBox->addButton(tr("Apply"), QDialogButtonBox::ApplyRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
    connect(apply, SIGNAL(clicked()), this, SLOT(applied()));
}

void ConfigDialog::layoutElements()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tabs);
    layout->addSpacing(10);
    layout->addWidget(buttonBox);

    this->setLayout(layout);
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
