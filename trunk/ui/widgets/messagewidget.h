/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QTextEdit>

/**
 * @brief Text Edit Widget for typing message.
 */
class MessageWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit MessageWidget(QWidget *parent = 0);

signals:
    /**
     * @brief Ctrl + Enter was pressed.
     */
    void accepted();

protected:
    virtual void keyReleaseEvent(QKeyEvent *e);

};

#endif // MESSAGEWIDGET_H
