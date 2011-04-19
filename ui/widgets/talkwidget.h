/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef TALKWIDGET_H
#define TALKWIDGET_H

#include <QWidget>
#include <gloox/jid.h>

class QTextEdit;
class MessageWidget;
class QPushButton;
class QWidget;

using namespace gloox;

/*
 History goes here.
 Message typing goes here.
 User info goes here.
 */
class TalkWidget : public QWidget
{
    Q_OBJECT
public:
    /*
     Constructor
     */
    explicit TalkWidget(QWidget *parent = 0, QWidget *info = 0);

    /*
     Target
     */
    void setTarget(const JID &target) { m_jid = target; }
    JID target() { return m_jid; }

signals:
    /*
     Send message
     */
    void sendMessage(const JID& target, const QString &msg);

public slots:
    /*
     Message recieved
     */
    void messageReceived(const QString &msg);

private slots:
    void sendMessage();

private:
    /*
     Setup UI
     */
    void createElements();
    void createButtons();
    void createTexts();
    void layoutElements();

    /*
     Elements
     */
    JID         m_jid;

    QTextEdit     *story;
    MessageWidget *message;

    QPushButton *send;

    QPushButton *bold;
    QPushButton *italic;
    QPushButton *underline;
    QPushButton *strikeout;

    QPushButton *fontSize;

    QPushButton *clear;

    QWidget     *info;
};

#endif // TALKWIDGET_H
