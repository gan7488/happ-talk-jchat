/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "talksdialog.h"
#include "widgets/talkwidget.h"
#include "widgets/talkerinfowidget.h"
#include "widgets/roominfowidget.h"
#include <QtGui>

TalksDialog::TalksDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::Window);
    this->setWindowIcon(QIcon(":/images/write.svg"));
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
    tabs->setIconSize(QSize(30,30));
    tabs->setTabPosition(QTabWidget::West);
    tabs->addTab(rooms, QIcon(":/images/users.svg"), tr("Rooms"));
    tabs->addTab(chats, QIcon(":/images/logo.svg"), tr("Chats"));
    tabs->addTab(advanced, QIcon(":/images/office.svg"), tr("Advanced"));

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
