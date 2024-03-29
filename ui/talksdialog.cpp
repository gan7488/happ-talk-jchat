/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "talksdialog.h"
#include "consts.h"
#include "widgets/talkwidget.h"
#include "widgets/talkerinfowidget.h"
#include "widgets/roominfowidget.h"
#include <QtGui>

/*
 Constructors
 */
TalksDialog::TalksDialog(QWidget *parent) :
    QDialog(parent), client(0)
{
    this->setWindowFlags(Qt::Window);
    this->setWindowIcon(QIcon(":/images/write.svg"));
    this->setMinimumSize(600, 400);
    createElements();
    layoutElements();
}
void TalksDialog::setMessaging(XMPPMessaging *messaging)
{
    client = messaging;
    if (client == 0) return;
    connect(client, SIGNAL(chatMessageRecieved(JID,QString)), this, SLOT(messageRecieved(JID,QString)));
    foreach(TalkWidget *item, talkWidgets)
    {
        connect(item, SIGNAL(sendMessage(JID,QString)), client, SLOT(sendChatMessage(JID,QString)));
    }
}

/*
 Events
 */
void TalksDialog::showEvent(QShowEvent *e)
{
    QSettings settings(QSettings::IniFormat, QSettings::SystemScope, org, app);
    restoreGeometry(settings.value("talksdialog/geometry").toByteArray());

    QDialog::showEvent(e);
}
void TalksDialog::closeEvent(QCloseEvent *e)
{
    QSettings settings(QSettings::IniFormat, QSettings::SystemScope, org, app);
    settings.setValue("talksdialog/geometry", saveGeometry());

    QDialog::closeEvent(e);
}

void TalksDialog::createElements()
{
    /*rooms = new QTabWidget();
    rooms->setTabPosition(QTabWidget::South);
    rooms->setTabsClosable(true);
    rooms->setMovable(true);
    connect(rooms, SIGNAL(tabCloseRequested(int)), this, SLOT(closeRoom(int)));
    */
    //TODO On close | handle event

    talks = new QTabWidget();
    talks->setTabPosition(QTabWidget::South);
    talks->setTabsClosable(true);
    talks->setMovable(true);
    connect(talks, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTalk(int)));
    //TODO On close | handle event

    /*advanced = new QTabWidget();
    advanced->setTabPosition(QTabWidget::South);
    advanced->setTabsClosable(true);
    advanced->setMovable(true);
    */
    //TODO On close | handle event

    tabs = new QTabWidget();
    tabs->setIconSize(QSize(30,30));
    tabs->setTabPosition(QTabWidget::West);
    tabs->addTab(talks, QIcon(":/images/user.svg"), tr("Talks"));
    //tabs->addTab(rooms, QIcon(":/images/users.svg"), tr("Rooms"));
    //tabs->addTab(advanced, QIcon(":/images/office.svg"), tr("Advanced"));

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
    // Find window and send message to that window
    // If widget wasn't found, create new widget.
    show();
    foreach(TalkWidget *item, talkWidgets)
    {
        if (item->target().bareJID() == from.bareJID())
        {
            talks->setCurrentWidget(item);
            item->messageReceived(msg);
            return;
        }
    }
    TalkWidget *talk = newTalk(from);
    talk->messageReceived(msg);
    talks->setCurrentWidget(talk);
}
TalkWidget* TalksDialog::newTalk(const JID &target)
{
    // Create new Widget and return it
    raise();
    TalkWidget *widget = new TalkWidget();
    widget->setTarget(target);

    if (client == 0) return widget;
    connect(widget, SIGNAL(sendMessage(JID,QString)), client, SLOT(sendChatMessage(JID,QString)));
    talkWidgets.append(widget);
    talks->addTab(widget, QString::fromUtf8(target.username().c_str()));
    return widget;
}

void TalksDialog::closeRoom(int index)
{
    rooms->removeTab(index);
}
void TalksDialog::closeTalk(int index)
{
    // Finish conversation
    TalkWidget *widget = (TalkWidget *)talks->currentWidget();
    client->endChat(widget->target());
    talkWidgets.removeOne(widget);
    talks->removeTab(index);
    delete widget;
}
