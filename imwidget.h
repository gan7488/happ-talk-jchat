/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef IMWIDGET_H
#define IMWIDGET_H

#include <QWidget>

namespace Ui {
    class IMWidget;
}

class IMWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IMWidget(QWidget *parent = 0);
    ~IMWidget();

private:
    Ui::IMWidget *ui;
};

#endif // IMWIDGET_H
