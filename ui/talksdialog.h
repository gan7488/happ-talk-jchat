/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef TALKSDIALOG_H
#define TALKSDIALOG_H

#include <QDialog>
#include <QMap>
#include <QList>
#include <gloox/jid.h>
#include "widgets/talkwidget.h"
#include "xmpp/xmppmessaging.h"

class QTabWidget;
class QString;

using namespace gloox;

/*
 Chats, Rooms, Rooms Settings
 */
class TalksDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TalksDialog(QWidget *parent = 0);

    void setMessaging(XMPPMessaging *messaging);

    /*
     Slots
     */
public slots:
    void messageRecieved(const JID &from, const QString &msg);

private slots:
    TalkWidget* newTalk(const JID &target);

    void closeRoom(int index);
    void closeTalk(int index);

protected:
    /*
     Events
     */
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    /*
     Setup UI
     */
    void createTabs();
    void layoutElements();

    /*
     Elements
     */
    QTabWidget *tabs;
    QTabWidget *rooms;
    QTabWidget *talks;
    QTabWidget *advanced;

    QList<TalkWidget *> talkWidgets;
    XMPPMessaging *client;
};

#endif // TALKSDIALOG_H
