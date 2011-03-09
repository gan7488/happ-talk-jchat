/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QTextEdit>

class MessageWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit MessageWidget(QWidget *parent = 0);

signals:
    void sendRequested();

public slots:

protected:
    virtual void keyReleaseEvent(QKeyEvent *e);

};

#endif // MESSAGEWIDGET_H
