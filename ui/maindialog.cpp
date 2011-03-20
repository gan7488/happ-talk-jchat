/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "maindialog.h"
#include "aboutdialog.h"
#include "talksdialog.h"
#include "configdialog.h"
#include "logindialog.h"
#include "xmpp/jclient.h"

#include <QtGui>
#include <QSystemTrayIcon>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setMinimumSize(250, 400);
    this->setMaximumWidth(400);
    this->setWindowTitle(tr("Jchat : Talkers"));
    this->setWindowIcon(QIcon(":/images/logo.svg"));
    createTree();
    createButtons();
    layoutElements();
    createWindows();
    createActions();
    createMenus();
    createTrayIcon();
    trayIcon->setVisible(true);
    client = new JClient();
}

MainDialog::~MainDialog()
{
    delete about;
    delete config;
    delete talks;
    delete login;
}

void MainDialog::showhide()
{
    setVisible(!isVisible());
}

void MainDialog::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

void MainDialog::createTree()
{
    buddies = new QTreeView();
}

void MainDialog::createButtons()
{
    top = new QPushButton(tr("-"));
    top->setFixedSize(80, 25);
    connect(top, SIGNAL(clicked()), this, SLOT(topClicked()));

    right = new QPushButton(tr(">"));
    right->setFixedSize(40, 55);
    connect(right, SIGNAL(clicked()), this, SLOT(rightClicked()));

    bottom = new QPushButton(tr("-"));
    bottom->setFixedSize(80, 25);
    connect(bottom, SIGNAL(clicked()), this, SLOT(bottomClicked()));

    left = new QPushButton(QIcon(":/images/folder.svg"), tr("<"));
    left->setFixedSize(40, 55);
    connect(left, SIGNAL(clicked()), this, SLOT(leftClicked()));
}

void MainDialog::createActions()
{
    showhideAction = new QAction(tr("Show / Hide"), this);
    connect(showhideAction, SIGNAL(triggered()), this, SLOT(showhide()));

    quitAction = new QAction(QIcon(":/images/exit.svg"), tr("Quit"), this);
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quitActionTriggered()));
}

void MainDialog::createMenus()
{
    menu = new QMenu(this);

    menu->addAction(showhideAction);
    menu->addSeparator();
    menu->addAction(quitAction);

    left->setMenu(menu);
}

void MainDialog::createWindows()
{
    about = new AboutDialog();
    config = new ConfigDialog();
    talks = new TalksDialog();
    login = new LoginDialog();
}

void MainDialog::createTrayIcon()
{
    /*trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);*/

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(menu);//trayIconMenu);
    trayIcon->setIcon(QIcon(":/images/logo.svg"));
    trayIcon->setToolTip("Jchat : talkers");

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void MainDialog::layoutElements()
{
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(top);
    vLayout->addWidget(bottom);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(left);
    hLayout->addStretch();
    hLayout->addLayout(vLayout);
    hLayout->addStretch();
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

void MainDialog::quitActionTriggered()
{
    //TODO close doors
    qApp->quit();
}

void MainDialog::showEvent(QShowEvent *e)
{
    int ret = login->exec();
    if (ret == QDialog::Accepted)
    {
        JID jid(login->getAccount().toStdString());
        client->connect(jid, login->getPassword());
    }
}

void MainDialog::iconActivated(QSystemTrayIcon::ActivationReason reason)
 {
     switch (reason) {
     case QSystemTrayIcon::Trigger:
     case QSystemTrayIcon::DoubleClick:
         showhide();
         break;
     case QSystemTrayIcon::MiddleClick:
         //TODO
         break;
     default:
         ;
     }
 }
