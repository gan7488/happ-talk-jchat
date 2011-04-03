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

class TalksDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TalksDialog(QWidget *parent = 0);

    void setMessaging(XMPPMessaging *messaging);
signals:

public slots:
    void messageRecieved(const JID &from, const QString &msg);

protected:
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    void createTabs();
    void layoutElements();

    QTabWidget *tabs;
    QTabWidget *rooms;
    QTabWidget *talks;
    QTabWidget *advanced;

    //QMap<JID, QWidget*> openedTalks;
    QList<TalkWidget *> talkWidgets;
    XMPPMessaging *client;
private slots:
    TalkWidget* newTalk(const JID &target);

    void closeRoom(int index);
    void closeTalk(int index);

};

#endif // TALKSDIALOG_H
