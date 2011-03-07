/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef IMWINDOW_H
#define IMWINDOW_H

#include <QMainWindow>

class QTabWidget;

class IMWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit IMWindow(QWidget *parent = 0);

signals:

public slots:

private:
    void createTabs();

    QTabWidget *mainTabs;
    QTabWidget *roomTabs;
    QTabWidget *imTabs;
    QTabWidget *advancedTabs;

private slots:

};

#endif // IMWINDOW_H
