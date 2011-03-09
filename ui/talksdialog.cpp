/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "talksdialog.h"
#include "talkwidget.h"
#include "talkerinfowidget.h"
#include "roominfowidget.h"
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

    RoomInfoWidget *info = new RoomInfoWidget();
    info->setVisible(false);
    rooms->addTab(new TalkWidget(), "Test 0");
    rooms->addTab(new TalkWidget(0, info), "Test 1");
    rooms->addTab(new TalkWidget(0, new RoomInfoWidget()), "Test 2");
    rooms->addTab(new TalkWidget(0, new RoomInfoWidget()), "Test 3");

    chats->addTab(new TalkWidget(0, new TalkerInfoWidget()), "IM 1");
    chats->addTab(new TalkWidget(0, new TalkerInfoWidget()), "IM 2");
    chats->addTab(new TalkWidget(0, new TalkerInfoWidget()), "IM 3");
}

void TalksDialog::layoutElements()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tabs);
    this->setLayout(layout);
}
