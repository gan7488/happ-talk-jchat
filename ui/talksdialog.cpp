/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "talksdialog.h"
#include "widgets/talkwidget.h"
#include "widgets/talkerinfowidget.h"
#include "widgets/roominfowidget.h"
#include <QtGui>

TalksDialog::TalksDialog(JClient *client, QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::Window);
    this->setWindowIcon(QIcon(":/images/write.svg"));
    this->setMinimumSize(600, 400);
    createTabs();
    layoutElements();
    this->client = client;
    connect(client, SIGNAL(messageRecieved(JID,QString)), this, SLOT(messageRecieved(JID,QString)));
}

void TalksDialog::createTabs()
{
    rooms = new QTabWidget();
    rooms->setTabPosition(QTabWidget::South);
    rooms->setTabsClosable(true);
    rooms->setMovable(true);
    connect(rooms, SIGNAL(tabCloseRequested(int)), this, SLOT(closeRoom(int)));
    //TODO On close | handle event

    talks = new QTabWidget();
    talks->setTabPosition(QTabWidget::South);
    talks->setTabsClosable(true);
    talks->setMovable(true);
    connect(talks, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTalk(int)));
    //TODO On close | handle event

    advanced = new QTabWidget();
    advanced->setTabPosition(QTabWidget::South);
    advanced->setTabsClosable(true);
    advanced->setMovable(true);
    //TODO On close | handle event

    tabs = new QTabWidget();
    tabs->setIconSize(QSize(30,30));
    tabs->setTabPosition(QTabWidget::West);
    tabs->addTab(talks, QIcon(":/images/user.svg"), tr("Talks"));
    tabs->addTab(rooms, QIcon(":/images/users.svg"), tr("Rooms"));
    tabs->addTab(advanced, QIcon(":/images/office.svg"), tr("Advanced"));

    RoomInfoWidget *info = new RoomInfoWidget();
    info->setVisible(false);
    /*rooms->addTab(new TalkWidget(), "Test 0");
    rooms->addTab(new TalkWidget(0, info), "Test 1");
    rooms->addTab(new TalkWidget(0, new RoomInfoWidget()), "Test 2");
    rooms->addTab(new TalkWidget(0, new RoomInfoWidget()), "Test 3");

    talks->addTab(new TalkWidget(0, new TalkerInfoWidget()), "IM 1");
    talks->addTab(new TalkWidget(0, new TalkerInfoWidget()), "IM 2");
    talks->addTab(new TalkWidget(0, new TalkerInfoWidget()), "IM 3");
*/
}

void TalksDialog::layoutElements()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tabs);
    this->setLayout(layout);
}

void TalksDialog::messageRecieved(const JID &from, const QString &msg)
{
    show();
    foreach(TalkWidget *item, talkWidgets)
    {
        if (item->target() == from)
        {
            item->messageReceived(msg);
            return;
        }
    }
    newTalk(from)->messageReceived(msg);;
}
TalkWidget* TalksDialog::newTalk(const JID &target)
{
    TalkWidget *widget = new TalkWidget();
    widget->setTarget(target);
    connect(widget, SIGNAL(sendMessage(JID,QString)), client, SLOT(sendMessage(JID,QString)));
    talkWidgets.append(widget);
    talks->addTab(widget, QString::fromUtf8(target.bare().c_str()));
    return widget;
}

void TalksDialog::closeRoom(int index)
{
    rooms->removeTab(index);
}
void TalksDialog::closeTalk(int index)
{
    TalkWidget *widget = (TalkWidget *)talks->currentWidget();
    client->endTalk(widget->target());
    talkWidgets.removeOne(widget);
    talks->removeTab(index);
    delete widget;
}