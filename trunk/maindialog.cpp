/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "maindialog.h"
#include "aboutdialog.h"
#include "talksdialog.h"
#include "configdialog.h"
#include "logindialog.h"

#include <QtGui>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setMinimumSize(250, 400);
    this->setMaximumWidth(400);
    this->setWindowTitle(tr("Jchat : Talkers"));
    createTree();
    createButtons();
    layoutElements();
    createWindows();
    createMenus();
}

MainDialog::~MainDialog()
{
    delete about;
    delete config;
    delete talks;
    delete login;
}

void MainDialog::createTree()
{
    buddies = new QTreeView();
}

void MainDialog::createButtons()
{
    top = new QPushButton(tr("-"));
    connect(top, SIGNAL(clicked()), this, SLOT(topClicked()));

    right = new QPushButton(tr(">"));
    connect(right, SIGNAL(clicked()), this, SLOT(rightClicked()));

    bottom = new QPushButton(tr("-"));
    connect(bottom, SIGNAL(clicked()), this, SLOT(bottomClicked()));

    left = new QPushButton(tr("<"));
    connect(left, SIGNAL(clicked()), this, SLOT(leftClicked()));
}

void MainDialog::createMenus()
{
    menu = new QMenu();

    menu->addAction("1");
    menu->addAction("2");
    menu->addAction("3");
    menu->addAction("4");
    menu->addSeparator();
    menu->addAction("1");
    menu->addAction("2");
    menu->addAction("3");
    menu->addAction("4");
    menu->addSeparator();
    exitAct = menu->addAction(tr("Exit"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exitActTriggered()));

    left->setMenu(menu);
}

void MainDialog::createWindows()
{
    about = new AboutDialog();
    config = new ConfigDialog();
    talks = new TalksDialog();
    login = new LoginDialog();
}

void MainDialog::layoutElements()
{
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(top);
    vLayout->addWidget(bottom);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(left);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(right);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(buddies);
    layout->addSpacing(10);
    layout->addLayout(hLayout);

    this->setLayout(layout);
}

void MainDialog::topClicked()
{
    talks->show();
}

void MainDialog::rightClicked()
{
    about->show();
}

void MainDialog::bottomClicked()
{
    config->show();
}

void MainDialog::leftClicked()
{

}

void MainDialog::exitActTriggered()
{
    this->close();
}

void MainDialog::showEvent(QShowEvent *e)
{
    login->show();
}

