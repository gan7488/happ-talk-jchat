/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QTextEdit>

/*
 Widget for typing message.
 TODO:
    1) IntelliType (or something like that) :D
    2) Draw smiles or not?
 */
class MessageWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit MessageWidget(QWidget *parent = 0);

signals:
    /*
     Signals
     */
    void accepted();

protected:
    virtual void keyReleaseEvent(QKeyEvent *e);

};

#endif // MESSAGEWIDGET_H
