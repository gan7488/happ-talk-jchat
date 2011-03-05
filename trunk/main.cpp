/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*
HOWTO: Styles

    QFile file(":/qss/" + sheetName.toLower() + ".qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui.styleTextEdit->setPlainText(styleSheet);
    qApp->setStyleSheet(styleSheet);
*/

/*
 HOWTO: Langs
QTranslator translator;
     translator.load(QString("arrowpad_") + locale);
     app.installTranslator(&translator);
*/
