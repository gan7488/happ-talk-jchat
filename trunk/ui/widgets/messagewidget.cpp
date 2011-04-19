/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "messagewidget.h"
#include <QKeyEvent>

MessageWidget::MessageWidget(QWidget *parent) :
    QTextEdit(parent)
{
}

void MessageWidget::keyReleaseEvent(QKeyEvent *e)
{
    if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Return)
        emit accepted();
}
