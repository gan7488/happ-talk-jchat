/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include <QtGui/QApplication>
#include <QtDebug>
#include <QFile>
#include "ui/maindialog.h"
#include "consts.h"

/*
 Entry point. No comments.
 */
int main(int argc, char *argv[])
{
    qApp->setApplicationName(app);
    qApp->setOrganizationName(org);

    QApplication a(argc, argv);

    a.setQuitOnLastWindowClosed(false);
    MainDialog w;
    w.show();

    return a.exec();
}
