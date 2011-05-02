/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QList>
#include <QSystemTrayIcon>
#include "xmpp/xmppclient.h"
#include "xmpp/xmppmessaging.h"
#include "xmpp/xmpproster.h"


class QMenu;
class QTreeWidget;
class QListWidget;
class QPushButton;
class QListWidgetItem;

class LoginDialog;
class AboutDialog;
class ConfigDialog;
class TalksDialog;

class MainDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

signals:

public slots:
    void showhide();

protected:
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    void createActions();
    void createButtons();
    void createTrayIcon();
    //void createTree();
    void createUserList();
    void createMenus();
    void createWindows();
    void layoutElements();

    AboutDialog     *about;
    ConfigDialog    *config;
    LoginDialog     *login;
    TalksDialog     *talks;

    QTreeWidget *buddies;
    QListWidget *userList;

    QPushButton *top;
    QPushButton *right;
    QPushButton *bottom;
    QPushButton *left;

    QMenu *menu;
    QMenu *statusMenu;

    QAction *beginTalkAction;

    QAction *subscribeAction;
    QAction *unsubscribeAction;

    QAction *configAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *showhideAction;
    QAction *quitAction;

    QAction *addItemAction;
    QAction *removeItemAction;

    QList<QAction *> statusActions;

    QSystemTrayIcon *trayIcon;

    XMPPClient      *m_client;
    XMPPMessaging   *m_messaging;
    XMPPRoster      *m_roster;

private slots:
    void addItemTriggered();
    void removeItemTriggered();

    void subscribeActionTriggered();
    void unsubscribeActionTriggered();

    void updateUserList(const Roster &roster);
    void disconnected(ConnectionError e);

    void itemAdded (const JID &jid);
    void itemRemoved (const JID &jid);
    void itemUpdated (const JID &jid);

    void itemSubscribed (const JID &jid);
    void itemUnsubscribed (const JID &jid);

    void rosterPresence (const RosterItem &item, const QString& resource, Presence::PresenceType presence, const QString& msg);

    void subscriptionRequest (const JID &jid, const QString& msg);
    void unsubscriptionRequest (const JID &jid, const QString& msg);


    void rosterRecieved (const Roster &roster);

    void loginAccepted();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void topClicked();
    void rightClicked();
    void bottomClicked();
    void leftClicked();

    void beginTalk();

    void configActionTriggered();
    void aboutActionTriggered();
    void aboutQtActionTriggered();
    void quitActionTriggered();

    void setAvailableStatus();
    void setAwayStatus();
    void setDNDStatus();
    void setInvisibleStatus();
    void setOfflineStatus();

    void userListClicked(QListWidgetItem * item);

};

#endif // MAINDIALOG_H
