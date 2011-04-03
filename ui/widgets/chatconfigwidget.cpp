/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "chatconfigwidget.h"
#include <QtGui>
#include <QSvgWidget>

ChatConfigWidget::ChatConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    createElements();
    layoutElements();
}

void ChatConfigWidget::load()
{

}

void ChatConfigWidget::save()
{

}

void ChatConfigWidget::createElements()
{
    pic = new QSvgWidget(":/images/users.svg");
    pic->setFixedSize(100,100);
}
void ChatConfigWidget::layoutElements()
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(new QLabel("CHATS SETTINGS GOES HERE\n"
                                  "SOMETHING LIKE MESSAGES FROMAT\n"
                                  "OR SMILES PACK, etc."));
    hLayout->addStretch();
    hLayout->addWidget(pic);
    this->setLayout(hLayout);
}
