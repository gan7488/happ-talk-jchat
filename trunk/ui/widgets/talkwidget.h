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

/**
 * @brief Widget that implements the conversation.
 */
class TalkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TalkWidget(QWidget *parent = 0, QWidget *info = 0);

    /**
     * @brief Set companion.
     * @param target Companions JID.
     */
    void setTarget(const JID &target) { m_jid = target; }
    /**
     * @brief Get companion.
     */
    JID target() { return m_jid; }

signals:
    /**
     * @brief Send message.
     * @param target For whom the message is intended.
     * @param msg Message to send.
     */
    void sendMessage(const JID& target, const QString &msg);

public slots:
    /**
     * @brief Message recieved from @ref target();
     * @param msg Recieved message.
     */
    void messageReceived(const QString &msg);

private slots:
    void sendMessage();

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
    JID         m_jid;

    QTextEdit     *story;
    MessageWidget *message;

    QPushButton *send;

    QPushButton *bold;
    QPushButton *italic;
    QPushButton *underline;
    QPushButton *strikeout;

    QPushButton *fontSize;

    QWidget     *info;
};

#endif // TALKWIDGET_H
