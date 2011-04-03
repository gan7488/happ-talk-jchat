/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  DO IT!
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifndef TALKWIDGET_H
#define TALKWIDGET_H

#include <QWidget>
#include <gloox/jid.h>

class QTextEdit;
class MessageWidget;
class QPushButton;
class QWidget;

using namespace gloox;

class TalkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TalkWidget(QWidget *parent = 0, QWidget *info = 0);

    void setTarget(const JID &target) { jid = target; }
    JID target() { return jid; }
signals:
    void sendMessage(const JID& target, const QString &msg);
public slots:
    void messageReceived(const QString &msg);
private:
    void createTexts();
    void createButtons();
    void layoutElements();

    JID jid;
    QTextEdit *story;
    MessageWidget *message;

    QPushButton *send;

    QPushButton *bold;
    QPushButton *italic;
    QPushButton *underline;
    QPushButton *strikeout;

    QPushButton *fontSize;

    QPushButton *clear;

    QWidget *info;

private slots:
    void sendMessage();
};

#endif // TALKWIDGET_H
