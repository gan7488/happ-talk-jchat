/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "jclient.h"

class QMenu;
class QTreeView;
class QPushButton;

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

protected:
    void showEvent(QShowEvent *e);

private:
    void createTree();
    void createButtons();
    void createMenus();
    void createWindows();
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
    QAction *exitAct;

    JClient *client;

private slots:
    void topClicked();
    void rightClicked();
    void bottomClicked();
    void leftClicked();

    void exitActTriggered();
};

#endif // MAINDIALOG_H
