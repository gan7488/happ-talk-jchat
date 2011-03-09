/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef TALKSDIALOG_H
#define TALKSDIALOG_H

#include <QDialog>

class QTabWidget;

class TalksDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TalksDialog(QWidget *parent = 0);

signals:

public slots:

private:
    void createTabs();
    void layoutElements();

    QTabWidget *tabs;
    QTabWidget *rooms;
    QTabWidget *chats;
    QTabWidget *advanced;

private slots:

};

#endif // TALKSDIALOG_H
