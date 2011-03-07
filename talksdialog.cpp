/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "talksdialog.h"
#include <QtGui>

TalksDialog::TalksDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::Window);
    createTabs();
    layoutElements();
}

void TalksDialog::createTabs()
{
    rooms = new QTabWidget();
    rooms->setTabPosition(QTabWidget::South);
    rooms->setTabsClosable(true);
    //TODO On close | handle event

    chats = new QTabWidget();
    chats->setTabPosition(QTabWidget::South);
    chats->setTabsClosable(true);
    //TODO On close | handle event

    advanced = new QTabWidget();
    advanced->setTabPosition(QTabWidget::South);
    advanced->setTabsClosable(true);
    //TODO On close | handle event

    tabs = new QTabWidget();
    tabs->setTabPosition(QTabWidget::West);
    tabs->addTab(rooms, tr("Rooms"));
    tabs->addTab(chats, tr("Chats"));
    tabs->addTab(advanced, tr("Advanced"));
}

void TalksDialog::layoutElements()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tabs);
    this->setLayout(layout);
}
