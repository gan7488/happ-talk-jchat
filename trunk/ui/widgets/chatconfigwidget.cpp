/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "chatconfigwidget.h"
#include <QtGui>
#include <QSvgWidget>

/*
 Constructors
 */
ChatConfigWidget::ChatConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWhatsThis(tr("Chat settings.<br>"
                          "Intellisense for message window and etc."));

    createElements();
    layoutElements();
}

/*
 Setup UI
 */
void ChatConfigWidget::createElements()
{
    /*
     TODO
     */
}
void ChatConfigWidget::layoutElements()
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(new QLabel("CHATS SETTINGS GOES HERE\n"
                                  "SOMETHING LIKE MESSAGES FROMAT\n"
                                  "OR SMILES PACK, etc."));
    hLayout->addStretch();

    QSvgWidget *pic = new QSvgWidget(":/images/users.svg");
    pic->setFixedSize(100,100);

    hLayout->addWidget(pic);
    this->setLayout(hLayout);
}

/*
 Slots
 */

void ChatConfigWidget::load()
{

}

void ChatConfigWidget::save()
{

}
