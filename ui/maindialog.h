/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QSystemTrayIcon>

class QMenu;
class QTreeView;
class QPushButton;
template <typename T> class QList;

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
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *event);

private:
    void createTree();
    void createButtons();
    void createMenus();
    void createActions();
    void createWindows();
    void createTrayIcon();
    void layoutElements();

    LoginDialog *login;
    AboutDialog *about;
    ConfigDialog *config;
    TalksDialog *talks;

    QTreeView *buddies;

    QPushButton *top;
    QPushButton *right;
    QPushButton *bottom;
    QPushButton *left;

    QMenu *menu;
    //QAction *aboutAction;
    QAction *showhideAction;
    QAction *quitAction;
    QList<QAction *>* statusActions;

    QSystemTrayIcon *trayIcon;

    JClient* client;

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void topClicked();
    void rightClicked();
    void bottomClicked();
    void leftClicked();

    void quitActionTriggered();
};

#endif // MAINDIALOG_H
