/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "maindialog.h"
#include "aboutdialog.h"
#include "talksdialog.h"
#include "configdialog.h"
#include "logindialog.h"
#include "consts.h"
#include "useritem.h"
#include <gloox/rostermanager.h>
#include <gloox/rosteritem.h>

#include <QtGui>
#include <QListWidget>

#include <QStringList>

MainDialog::MainDialog(QWidget *parent) :
        QDialog(parent), m_client(0), m_messaging(0)
{
    this->setMinimumSize(250, 400);
    this->setMaximumWidth(400);
    this->setWindowTitle(tr("Jchat : Talkers"));
    this->setWindowIcon(QIcon(":/images/logo.svg"));

    createUserList();
    createButtons();
    layoutElements();
    createWindows();
    createActions();
    createMenus();
    createTrayIcon();
    trayIcon->setVisible(true);
}

MainDialog::~MainDialog()
{
    if (m_client)
    {
        delete m_client;
    }
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
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, org, app);
    restoreGeometry(settings.value("maindialog/geometry").toByteArray());

    QDialog::showEvent(e);

    if (!m_client || !m_client->authed())
    {
        login->show();
        login->setFocus();
    }
}

void MainDialog::closeEvent(QCloseEvent *e)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, org, app);
    settings.setValue("maindialog/geometry", saveGeometry());

    hide();
    e->ignore();
}

void MainDialog::createUserList()
{
    userList = new QListWidget();

    UserItem* userListDelegate = new UserItem();
    userList->setItemDelegate(userListDelegate);
    connect(userList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(userListClicked(QListWidgetItem*)));
}

void MainDialog::createButtons()
{
    top = new QPushButton(tr("Talks"));
    top->setFixedSize(80, 25);
    connect(top, SIGNAL(clicked()), this, SLOT(topClicked()));

    right = new QPushButton(QIcon(":/images/status-avaliable.svg"), "");
    right->setIconSize(QSize(50,50));
    right->setFixedSize(60, 55);

    bottom = new QPushButton(tr("Config"));
    bottom->setFixedSize(80, 25);
    connect(bottom, SIGNAL(clicked()), this, SLOT(bottomClicked()));

    left = new QPushButton(QIcon(":/images/folder.svg"), "");
    left->setIconSize(QSize(50,50));
    left->setFixedSize(60, 55);
}

void MainDialog::createActions()
{
    QAction *stat;

    stat = new QAction(QIcon(":/images/status-avaliable.svg") , tr("Avaliable"), this);
    connect(stat, SIGNAL(triggered()), this, SLOT(setAvailableStatus()));
    stat->setCheckable(true);
    statusActions.append(stat);

    stat = new QAction(QIcon(":/images/status-away.svg") , tr("Away"), this);
    connect(stat, SIGNAL(triggered()), this, SLOT(setAwayStatus()));
    stat->setCheckable(true);
    statusActions.append(stat);

    stat = new QAction(QIcon(":/images/status-dnd.svg") , tr("Do Not Disturbed"), this);
    connect(stat, SIGNAL(triggered()), this, SLOT(setDNDStatus()));
    stat->setCheckable(true);
    statusActions.append(stat);

    stat = new QAction(QIcon(":/images/status-invisible.svg") , tr("Invisible"), this);
    connect(stat, SIGNAL(triggered()), this, SLOT(setInvisibleStatus()));
    stat->setCheckable(true);
    statusActions.append(stat);

    stat = new QAction(QIcon(":/images/status-offline.svg") , tr("Offline"), this);
    connect(stat, SIGNAL(triggered()), this, SLOT(setOfflineStatus()));
    stat->setCheckable(true);
    statusActions.append(stat);

    beginTalkAction = new QAction(QIcon(":/images/info.svg"), tr("New talk"), this);
    connect(beginTalkAction, SIGNAL(triggered()), this, SLOT(beginTalk()));

    subscribeAction = new QAction(tr("Subscribe"), this);
    connect(subscribeAction, SIGNAL(triggered()), this, SLOT(subscribeActionTriggered()));

    unsubscribeAction = new QAction(tr("Unsubscribe"), this);
    connect(unsubscribeAction, SIGNAL(triggered()), this, SLOT(unsubscribeActionTriggered()));


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

    addItemAction = new QAction(tr("Add item"), this);
    connect(addItemAction, SIGNAL(triggered()), this, SLOT(addItemTriggered()));

    removeItemAction = new QAction(tr("Remove item"), this);
    connect(removeItemAction, SIGNAL(triggered()), this, SLOT(removeItemTriggered()));
}

void MainDialog::createMenus()
{
    menu = new QMenu(this);

    statusMenu = new QMenu(tr("Status"));
    statusMenu->addActions(statusActions);

    menu->addMenu(statusMenu);
    menu->addSeparator();
    menu->addAction(beginTalkAction);
    menu->addSeparator();

    QMenu *subMenu = new QMenu(tr("Managing"));
    subMenu->addAction(subscribeAction);
    subMenu->addAction(addItemAction);
    subMenu->addSeparator();
    subMenu->addAction(unsubscribeAction);
    subMenu->addAction(removeItemAction);

    menu->addMenu(subMenu);
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
    about   = new AboutDialog();
    config  = new ConfigDialog();
    talks   = new TalksDialog();
    login   = new LoginDialog();

    connect(login, SIGNAL(accepted()), this, SLOT(loginAccepted()));
}

void MainDialog::createTrayIcon()
{
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
    layout->addWidget(userList);
    layout->addSpacing(10);
    layout->addLayout(hLayout);

    this->setLayout(layout);
}

void MainDialog::loginAccepted()
{
    JID jid;
    jid.setUsername(login->username().toStdString());
    jid.setServer(login->server().toStdString());
    jid.setResource("jchat");
    if (m_client)
    {
        delete m_client;
        m_client = 0;
    }
    m_client = new XMPPClient(jid, login->password());

    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       qApp->organizationName(), qApp->applicationName());

    QString proxy = settings.value("proxy/type", "none").toString().toLower();
    int port = settings.value("proxy/port", "-1").toInt();

    if (proxy == "socks5")
        m_client->setSOCKS5Proxy(settings.value("proxy/host").toString(), port,
                            settings.value("proxy/user").toString(),
                            settings.value("proxy/pass").toString());
    else if (proxy == "http")
        m_client->setHTTPProxy(settings.value("proxy/host").toString(), port,
                            settings.value("proxy/user").toString(),
                            settings.value("proxy/pass").toString());

    m_messaging = new XMPPMessaging();
    m_roster = new XMPPRoster();
    connect(m_client, SIGNAL(disconnected(ConnectionError)), this, SLOT(disconnected(ConnectionError)));
    connect(m_roster, SIGNAL(itemAdded(JID)), this, SLOT(itemAdded(JID)));
    connect(m_roster, SIGNAL(itemRemoved(JID)), this, SLOT(itemRemoved(JID)));
    connect(m_roster, SIGNAL(itemUpdated(JID)), this, SLOT(itemUpdated(JID)));

    connect(m_roster, SIGNAL(subscriptionRequest(JID,QString)), this, SLOT(subscriptionRequest(JID,QString)));
    connect(m_roster, SIGNAL(unsubscriptionRequest(JID,QString)), this, SLOT(unsubscriptionRequest(JID,QString)));

    connect(m_roster, SIGNAL(itemSubscribed(JID)), this, SLOT(itemSubscribed(JID)));
    connect(m_roster, SIGNAL(itemUnsubscribed(JID)), this, SLOT(itemUnsubscribed(JID)));

    connect(m_roster,SIGNAL(selfPresence(RosterItem,QString,Presence::PresenceType,QString)),
            this, SLOT(selfPresence(RosterItem,QString,Presence::PresenceType,QString)));
    connect(m_roster, SIGNAL(rosterPresence(RosterItem,QString,Presence::PresenceType,QString)),
            this, SLOT(rosterPresence(RosterItem,QString,Presence::PresenceType,QString)));

    connect(m_roster, SIGNAL(rosterRecieved(Roster)), this, SLOT(rosterRecieved(Roster)));

    *m_client += m_messaging;
    *m_client += m_roster;

    m_client->connect();
    talks->setMessaging(m_messaging);
}

void MainDialog::topClicked()
{
    talks->show();
}

void MainDialog::bottomClicked()
{
    config->show();
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
    qApp->aboutQt();
}

void MainDialog::quitActionTriggered()
{
    qApp->quit();
}

void MainDialog::iconActivated(QSystemTrayIcon::ActivationReason reason)
 {
     switch (reason) {
     case QSystemTrayIcon::Trigger:
     case QSystemTrayIcon::DoubleClick:
         showhide();
         break;
     }
 }

void MainDialog::rosterRecieved (const Roster &roster)
{
    updateUserList(roster);
}

void MainDialog::beginTalk()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("New IM"),
                                              tr("JID:"), QLineEdit::Normal, QString(), &ok);
    if (ok && !text.isEmpty())
    {
        JID jid(text.toStdString());
        talks->messageRecieved(jid, QString());
    }
}

void MainDialog::setAvailableStatus()
{
    if (!m_client || !m_client->authed())
        login->show();
    else
    {
        foreach(QAction *action, statusActions)
            action->setChecked(false);
        m_client->setPresence(gloox::Presence::Available);
    }
}

void MainDialog::setAwayStatus()
{
    if (!m_client || !m_client->authed())
        login->show();
    else
    {
        foreach(QAction *action, statusActions)
            action->setChecked(false);
        m_client->setPresence(gloox::Presence::Away);
    }
}

void MainDialog::setDNDStatus()
{
    if (!m_client || !m_client->authed())
        login->show();
    else
    {
        foreach(QAction *action, statusActions)
            action->setChecked(false);
        m_client->setPresence(gloox::Presence::DND);
    }
}

void MainDialog::setInvisibleStatus()
{
    if (!m_client || !m_client->authed())
        login->show();
    else
    {
        foreach(QAction *action, statusActions)
            action->setChecked(false);
        m_client->setPresence(gloox::Presence::Unavailable);
    }
}

void MainDialog::setOfflineStatus()
{
    if (m_client)
        m_client->disconnect();
}

void MainDialog::updateUserList(const Roster &roster)
{
    userList->clear();

    std::map<const std::string, RosterItem*>::const_iterator i = roster.begin();
    for(int row = 1; i != roster.end(); i++, row++)
    {
        RosterItem* rosterItem = i->second;

        QListWidgetItem* item = new QListWidgetItem();
        item->setToolTip(QString::fromUtf8(rosterItem->name().c_str()));

        QVariant nick;
        nick.setValue(QString::fromUtf8(rosterItem->name().c_str()));
        qDebug() << "LALALA  " << rosterItem->name().c_str();
        QVariant status;
        QVariant presence;
        const Resource * resource = rosterItem->highestResource();
        if (resource)
        {
            status.setValue(QString::fromUtf8(resource->message().c_str()));

            switch (resource->presence())
            {
                case Presence::Available: presence = tr("Available"); break;
                case Presence::Away: case Presence::XA: presence = tr("Away"); break;
                case Presence::DND: presence = tr("DND"); break;
                default: presence = tr("Unavailable"); break;
            }
        }
        else
            presence = tr("Offline");
        presence.setValue(presence);
        QVariant jid;
        jid.setValue(QString::fromUtf8(rosterItem->jid().c_str()));
        item->setData(UserItem::userNick, nick);
        item->setData(UserItem::userStatus, status);
        item->setData(UserItem::userJID, jid);
        item->setData(UserItem::userPresence, presence);
        userList->insertItem(row, item);
    }
}

void MainDialog::disconnected(ConnectionError e)
{
    userList->clear();
    if (e == ConnUserDisconnected) return;
    QString message;
    switch (e)
    {
        case ConnProxyAuthRequired: message = tr("Proxy auth required"); break;
        case ConnProxyAuthFailed: message = tr("Proxy auth failed"); break;
        case ConnConnectionRefused: message = tr("Connection was refused"); break;
        case ConnAuthenticationFailed : message = tr("Authentication failed"); break;
        case ConnUserDisconnected: message = tr("User disconnected"); break;
        default: message = tr("Unrecognized or internal problems"); break;
    }

    trayIcon->showMessage(tr("Some troubles!"), message);
}

void MainDialog::itemAdded(const JID &jid)
{
    if (m_client && m_client->authed())
    {
        m_client->roster()->synchronize();
        updateUserList(*m_client->roster()->roster());

    }
    trayIcon->showMessage(tr("User List"), tr("Item %1 added").arg(QString::fromUtf8(jid.full().c_str())));
}

void MainDialog::itemRemoved(const JID &jid)
{
    if (m_client && m_client->authed())
    {
        m_client->roster()->synchronize();
        updateUserList(*m_client->roster()->roster());

    }
    trayIcon->showMessage(tr("User List"), tr("Item %1 removed").arg(QString::fromUtf8(jid.full().c_str())));
}

void MainDialog::itemUpdated(const JID &jid)
{
    if (m_client && m_client->authed())
    {
        m_client->roster()->synchronize();
        updateUserList(*m_client->roster()->roster());

    }
    trayIcon->showMessage(tr("User List"), tr("Item %1 updated").arg(QString::fromUtf8(jid.full().c_str())));
}

void MainDialog::itemSubscribed (const JID &jid)
{
    trayIcon->showMessage(tr("User List"), tr("Item %1 subscribed").arg(QString::fromUtf8(jid.full().c_str())));
}

void MainDialog::itemUnsubscribed (const JID &jid)
{
    trayIcon->showMessage(tr("User List"), tr("Item %1 unsubscribed").arg(QString::fromUtf8(jid.full().c_str())));
}
void MainDialog::selfPresence (const RosterItem &item, const QString& resource, Presence::PresenceType presence, const QString& msg)
{
    foreach(QAction *action, statusActions)
        action->setChecked(false);
    switch (presence)
    {
        case Presence::Unavailable: statusActions.at(3)->setChecked(true); break;
        case Presence::Available: statusActions.at(0)->setChecked(true); break;
        case Presence::Away: case Presence::XA: statusActions.at(1)->setChecked(true); break;
        case Presence::DND: statusActions.at(2)->setChecked(true); break;
    }
}

void MainDialog::rosterPresence (const RosterItem &item, const QString& resource, Presence::PresenceType presence, const QString& msg)
{
    if (m_client && m_client->authed())
    {
        updateUserList(*m_client->roster()->roster());
    }

    QString name;
    name = QString::fromUtf8(item.name().c_str());
    if (name.isNull() || name.isEmpty())
        name = QString::fromUtf8(item.jid().c_str());

    QString status;
    switch (presence)
    {
        case Presence::Available: status = tr("available"); break;
        case Presence::Away: case Presence::XA: status = tr("away"); break;
        case Presence::DND: status = tr("DND"); break;
        default: status = tr("offline"); break;
    }


    trayIcon->showMessage(tr("%1 now is %2").arg(name).arg(status), msg);
}

void MainDialog::subscriptionRequest (const JID &jid, const QString& msg)
{
    if (!m_client || !m_client->authed()) return;
    if (QMessageBox::question(this, tr("%1 requesting subscriprtion").arg(QString::fromUtf8(jid.bare().c_str())),
                              tr("%1 requesting subscriprtion<br>%2").arg(QString::fromUtf8(jid.bare().c_str())).arg(msg), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
    {
        m_client->roster()->ackSubscriptionRequest(jid, true);
    }
    else
    {
        m_client->roster()->ackSubscriptionRequest(jid, false);
    }
}

void MainDialog::unsubscriptionRequest (const JID &jid, const QString& msg)
{
    if (!m_client || !m_client->authed()) return;
    if (QMessageBox::question(this, tr("Unsubscribe %1").arg(QString::fromUtf8(jid.bare().c_str())),
                              tr("Unsubscribe %1<br>%2").arg(QString::fromUtf8(jid.bare().c_str())).arg(msg), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
    {
        m_client->roster()->unsubscribe(jid);
    }
}

void MainDialog::subscribeActionTriggered()
{
    if (!m_client || !m_client->authed()) return;

    if (userList->selectedItems().count() > 0)
    {
        foreach(QListWidgetItem *item, userList->selectedItems())
        {
            QString nick = qvariant_cast<QString>(item->data(UserItem::userJID));

            if (QMessageBox::question(this, tr("Subscribe item %1").arg(nick),
                                      tr("Subscribe item %1").arg(nick), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
            {
                JID jid(nick.toStdString());
                std::list<std::string> groups;
                groups.push_front(QString("Buddies").toStdString());
                m_client->roster()->subscribe(jid, jid.username(), groups, "Please, authorize me!");
                //JID jid(nick.toStdString());
                //m_client->roster()->unsubscribe(jid);
            }
        }
    }
    else
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Subscribe"),
                                                  tr("JID:"), QLineEdit::Normal,
                                                  QString(), &ok);
        if (ok && !text.isEmpty())
        {
            JID jid(text.toStdString());
            std::list<std::string> groups;
            groups.push_front(QString("Buddies").toStdString());
            m_client->roster()->subscribe(jid, jid.username(), groups, "Please, authorize me!");
        }
    }
}

void MainDialog::unsubscribeActionTriggered()
{
    if (!m_client || !m_client->authed()) return;

    if (userList->selectedItems().count() > 0)
    {
        foreach(QListWidgetItem *item, userList->selectedItems())
        {
            QString nick = qvariant_cast<QString>(item->data(UserItem::userJID));

            if (QMessageBox::question(this, tr("Unsubscribe item %1").arg(nick),
                                      tr("Unsubscribe item %1").arg(nick), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
            {
                JID jid(nick.toStdString());
                m_client->roster()->unsubscribe(jid);
            }
        }
    }
    else
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Unsubscribe"),
                                                  tr("JID:"), QLineEdit::Normal,
                                                  QString(), &ok);
        if (ok && !text.isEmpty())
        {
            JID jid(text.toStdString());
            m_client->roster()->unsubscribe(jid);
        }
    }
}

void MainDialog::userListClicked(QListWidgetItem * item)
{
    QString nick = qvariant_cast<QString>(item->data(UserItem::userJID));
    JID jid(nick.toStdString());
    talks->messageRecieved(jid, QString());
}

void MainDialog::addItemTriggered()
{
    if (!m_client || !m_client->authed()) return;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Add item"),
                                                  tr("JID:"), QLineEdit::Normal,
                                                  QString(), &ok);
    if (ok && !text.isEmpty())
    {
        JID jid(text.toStdString());
        std::list<std::string> groups;
        groups.push_front(QString("Buddies").toStdString());
        m_client->roster()->add(jid, jid.username(), groups);
    }
}

void MainDialog::removeItemTriggered()
{
    if (!m_client || !m_client->authed()) return;

    if (userList->selectedItems().count() > 0)
    {
        foreach(QListWidgetItem *item, userList->selectedItems())
        {
            QString nick = qvariant_cast<QString>(item->data(UserItem::userJID));

            if (QMessageBox::question(this, tr("Remove item %1").arg(nick),
                                      tr("Remove this item from user list?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
            {
                m_client->roster()->remove(JID(nick.toStdString()));
                //JID jid(nick.toStdString());
                //m_client->roster()->unsubscribe(jid);
            }
        }
    }
    else
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Remove item"),
                                                  tr("JID:"), QLineEdit::Normal,
                                                  QString(), &ok);
        if (ok && !text.isEmpty())
        {
            JID jid(text.toStdString());
            m_client->roster()->remove(jid);
        }
    }
}
