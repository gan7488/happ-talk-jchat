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

/**
 * @brief Chats, Rooms, Rooms Settings
 */
class TalksDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TalksDialog(QWidget *parent = 0);

    void setMessaging(XMPPMessaging *messaging);

public slots:
    /**
     * @brief Occures when message was recieved.
     * @param from Message was recieved from this jid
     * @param msg Recieved message.
     */
    void messageRecieved(const JID &from, const QString &msg);

private slots:
    TalkWidget* newTalk(const JID &target);

    void closeRoom(int index);
    void closeTalk(int index);

protected:
    /**
     * @brief Occurs when the dialog is shown.
     * @param e Event arguments
     */
    void showEvent(QShowEvent *e);
    /**
     * @brief Occurs when the dialog is closed.
     * @param e Event arguments
     */
    void closeEvent(QCloseEvent *e);

private:
    /**
     * @brief Creating widgets.
     */
    void createElements();
    /**
     * @brief Layout widgets.
     */
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
