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


class QMenu;
class QTreeView;
class QPushButton;

class LoginDialog;
class AboutDialog;
class ConfigDialog;
class TalksDialog;

class JClient;

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
    void reject() {}
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    void createActions();
    void createButtons();
    void createTrayIcon();
    void createTree();
    void createMenus();
    void createWindows();
    void layoutElements();

    AboutDialog     *about;
    ConfigDialog    *config;
    LoginDialog     *login;
    TalksDialog     *talks;

    QTreeView *buddies;

    QPushButton *top;
    QPushButton *right;
    QPushButton *bottom;
    QPushButton *left;

    QMenu *menu;
    QMenu *statusMenu;

    QAction *newTalk;

    QAction *configAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *showhideAction;
    QAction *quitAction;

    QList<QAction *> statusActions;

    QSystemTrayIcon *trayIcon;

    JClient* client;

    XMPPClient      *m_client;
    XMPPMessaging   *m_messaging;
private slots:
    void loginAccepted();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void topClicked();
    void rightClicked();
    void bottomClicked();
    void leftClicked();

    void configActionTriggered();
    void aboutActionTriggered();
    void aboutQtActionTriggered();
    void quitActionTriggered();
    void status();
};

#endif // MAINDIALOG_H
