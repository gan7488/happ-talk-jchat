/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "configdialog.h"
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
    tabs->addTab(new QLabel(), "ladg dfgd dsla");
    tabs->addTab(new QLabel(), " pi pbvxc ,m.   w ,cvb");
    tabs->addTab(new QLabel(), "45bhsd gf df s asg dfsg d ");
    tabs->addTab(new QLabel(), "45bhsd gf df s asg dfsg d ");
    tabs->addTab(new QLabel(), "45bhsd gf df s asg dfsg d ");
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
