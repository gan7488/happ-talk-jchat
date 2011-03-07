/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "imwindow.h"
#include "imwidget.h"
#include "roominfowidget.h"
#include "userinfowidget.h"
#include <QtGui>


IMWindow::IMWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createTabs();
}

void IMWindow::createTabs()
{
    mainTabs = new QTabWidget();
    mainTabs->setTabPosition(QTabWidget::West);
    this->setCentralWidget(mainTabs);

    roomTabs = new QTabWidget();
    roomTabs->setTabPosition(QTabWidget::South);
    mainTabs->addTab(roomTabs, tr("Rooms"));

    imTabs = new QTabWidget();
    imTabs->setTabPosition(QTabWidget::South);
    mainTabs->addTab(imTabs, tr("IMs"));

    advancedTabs = new QTabWidget();
    advancedTabs->setTabPosition(QTabWidget::South);
    mainTabs->addTab(advancedTabs, tr("Advanced"));

    roomTabs->addTab(new IMWidget(0, new UserInfoWidget()), "Lala");
}
