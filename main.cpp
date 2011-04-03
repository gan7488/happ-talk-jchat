/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include <QtGui/QApplication>
#include <QtDebug>
#include <QFile>
#include "ui/maindialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    MainDialog w;
    w.show();

    return a.exec();
}
