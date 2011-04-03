/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "maindialog.h"
#include "aboutdialog.h"
#include "talksdialog.h"
#include "configdialog.h"
#include "logindialog.h"
#include "xmpp/jclient.h"
#include "consts.h"

#include <QtGui>

MainDialog::MainDialog(QWidget *parent) :
        QDialog(parent), m_client(0), m_messaging(0)
{
    //client = new JClient(JID("jchat@jabber.uruchie.org"), QString("test"));
    //client->connect();

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
    //client = 0;
    //client = new JClient(JID("jchat@jabber.uruchie.org"), QString());
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

void MainDialog::showEvent(QShowEvent *e)
{
    QSettings settings(QSettings::IniFormat, QSettings::SystemScope, org, app);
    restoreGeometry(settings.value("maindialog/geometry").toByteArray());

    QDialog::showEvent(e);

    if (!m_client || !m_client->authed())
        login->show();

//    qDebug() << "pointer " << (int) client;
//    if (client != 0) return;
//    int ret = login->exec();
//    if (ret == QDialog::Accepted)
//    {
//        JID jid(login->getAccount().toStdString());
//        client = new JClient(jid, login->getPassword());
//        client->connect();

//        //client->connect(jid, login->getPassword());
//    }

}

void MainDialog::closeEvent(QCloseEvent *e)
{
    QSettings settings(QSettings::IniFormat, QSettings::SystemScope, org, app);
    settings.setValue("maindialog/geometry", saveGeometry());

    hide();
    e->ignore();
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
    right->setFixedSize(60, 55);
    connect(right, SIGNAL(clicked()), this, SLOT(rightClicked()));

    bottom = new QPushButton(tr("-"));
    bottom->setFixedSize(80, 25);
    connect(bottom, SIGNAL(clicked()), this, SLOT(bottomClicked()));

    left = new QPushButton(QIcon(":/images/folder.svg"), "");
    left->setFixedSize(60, 55);
    connect(left, SIGNAL(clicked()), this, SLOT(leftClicked()));
}

void MainDialog::createActions()
{
    QAction *stat;

    stat = new QAction(QIcon(":/images/status-avaliable.svg") , tr("Avaliable"), this);
    connect(stat, SIGNAL(triggered()), this, SLOT(status()));
    statusActions.append(stat);

    stat = new QAction(QIcon(":/images/status-away.svg") , tr("Away"), this);
    connect(stat, SIGNAL(triggered()), this, SLOT(status()));
    statusActions.append(stat);

    stat = new QAction(QIcon(":/images/status-dnd.svg") , tr("Do Not Disturbed"), this);
    connect(stat, SIGNAL(triggered()), this, SLOT(status()));
    statusActions.append(stat);

    stat = new QAction(QIcon(":/images/status-invisible.svg") , tr("Invisible"), this);
    connect(stat, SIGNAL(triggered()), this, SLOT(status()));
    statusActions.append(stat);

    stat = new QAction(QIcon(":/images/status-offline.svg") , tr("Offline"), this);
    connect(stat, SIGNAL(triggered()), this, SLOT(status()));
    statusActions.append(stat);


    configAction = new QAction(QIcon(":/images/preferences.svg"), tr("Preferences"), this);
    connect(configAction, SIGNAL(triggered()), this, SLOT(configActionTriggered()));

    aboutAction = new QAction(QIcon(":/images/home.svg"), tr("About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutActionTriggered()));

    aboutQtAction = new QAction(QIcon(":/images/home.svg"), tr("About Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQtActionTriggered()));

    showhideAction = new QAction(tr("Show / Hide"), this);
    connect(showhideAction, SIGNAL(triggered()), this, SLOT(showhide()));

    quitAction = new QAction(QIcon(":/images/exit.svg"), tr("Quit"), this);
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quitActionTriggered()));
}

void MainDialog::createMenus()
{
    menu = new QMenu(this);

    statusMenu = new QMenu(tr("Status"));
    statusMenu->addActions(statusActions);

    menu->addMenu(statusMenu);
    menu->addSeparator();
    menu->addAction(configAction);
    menu->addAction(aboutAction);
    menu->addAction(aboutQtAction);
    menu->addSeparator();

    menu->addAction(showhideAction);
    menu->addSeparator();
    menu->addAction(quitAction);

    left->setMenu(menu);
    right->setMenu(statusMenu);
}

void MainDialog::createWindows()
{
    about   = new AboutDialog(this);
    config  = new ConfigDialog(this);
    talks   = new TalksDialog(this);
    login   = new LoginDialog(this);

    connect(login, SIGNAL(accepted()), this, SLOT(loginAccepted()));
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

void MainDialog::loginAccepted()
{
    JID jid;
    jid.setUsername(login->username().toStdString());
    jid.setServer(login->server().toStdString());
    m_client = new XMPPClient(jid, login->password());
    m_messaging = new XMPPMessaging();
    m_client->attach(m_messaging);
    m_client->connect();
    talks->setMessaging(m_messaging);
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

void MainDialog::configActionTriggered()
{
    config->show();
}

void MainDialog::aboutActionTriggered()
{
    about->exec();
}
void MainDialog::aboutQtActionTriggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainDialog::quitActionTriggered()
{
    //TODO close doors
    qApp->quit();
}

void MainDialog::status()
{
    qDebug() << "change status";
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
