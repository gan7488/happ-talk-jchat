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

/**
 * @brief Main dialog.
 */
class MainDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

public slots:
    /**
     * @brief Show or hide dialog.
     */
    void showhide();

protected:
    /**
     * @brief Occurs when the dialog is shown.
     * @param e Event arguments.
     */
    void showEvent(QShowEvent *e);
    /**
     * @brief Occurs when the dialog is closed.
     * @param e Event arguments.
     */
    void closeEvent(QCloseEvent *e);

private:
    /*
     No Comments
     */
    void createActions();
    void createButtons();
    void createTrayIcon();
    void createUserList();
    void createMenus();
    void createWindows();
    void layoutElements();

    /*
     Elements
     */
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
    /*
     All handlers (Slots) goes here
     */
    /**
     * @brief addItem action triggered.
     */
    void addItemTriggered();
    /**
     * @brief removeItem action triggered.
     */
    void removeItemTriggered();

    /**
     * @brief subscribe action triggered.
     */
    void subscribeActionTriggered();
    /**
     * @brief unsubscribe action triggered.
     */
    void unsubscribeActionTriggered();

    /**
     * @brief Update user list.
     * @param roster Elements to be added to user list.
     */
    void updateUserList(const Roster &roster);
    /**
     * @brief The connection was aborted.
     * @param e The reason for the disconnection.
     */
    void disconnected(ConnectionError e);

    /**
     * @brief Occurs when an item has been added to roster.
     * @param jid JID of the added item.
     */
    void itemAdded (const JID &jid);
    /**
     * @brief Occurs when an item has been removed from roster.
     * @param jid JID of the removed item.
     */
    void itemRemoved (const JID &jid);
    /**
     * @brief Occurs when an item has been updated in roster.
     * @param jid JID of the updated item.
     */
    void itemUpdated (const JID &jid);

    /**
     * @brief Occurs when item was subscribed
     * @param jid JID of the subscribed item.
     */
    void itemSubscribed (const JID &jid);
    /**
     * @brief Occurs when item was unsubscribed.
     * @param jid JID of the unsubscribed item.
     */
    void itemUnsubscribed (const JID &jid);

    /*
     Presence
     */
    void selfPresence (const RosterItem &item, const QString& resource, Presence::PresenceType presence, const QString& msg);
    void rosterPresence (const RosterItem &item, const QString& resource, Presence::PresenceType presence, const QString& msg);

    /*
     Subscription requests
     */
    void subscriptionRequest (const JID &jid, const QString& msg);
    void unsubscriptionRequest (const JID &jid, const QString& msg);

    void rosterRecieved (const Roster &roster);

    void loginAccepted();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void topClicked();
    void bottomClicked();

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
