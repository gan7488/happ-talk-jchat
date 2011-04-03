/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef CHATCONFIGWIDGET_H
#define CHATCONFIGWIDGET_H

#include <QWidget>

class QSvgWidget;

class ChatConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatConfigWidget(QWidget *parent = 0);

    void load();
    void save();

signals:

public slots:
private:
    void createElements();
    void layoutElements();

    QSvgWidget *pic;

};

#endif // CHATCONFIGWIDGET_H
