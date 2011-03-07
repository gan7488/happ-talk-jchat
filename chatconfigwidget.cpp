/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "chatconfigwidget.h"
#include <QtGui>

ChatConfigWidget::ChatConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(new QLabel("CHATS SETTINGS GOES HERE"));
    this->setLayout(hLayout);

}
