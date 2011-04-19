/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef CHATCONFIGWIDGET_H
#define CHATCONFIGWIDGET_H

#include <QWidget>

/*
 Configuration. Chat configuration section.
 */
class ChatConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatConfigWidget(QWidget *parent = 0);

public slots:
    /*
     Slots
     */
    void load();
    void save();

private:
    /*
     Setup UI
     */
    void createElements();
    void layoutElements();

    /*
     Elements
     */
};

#endif // CHATCONFIGWIDGET_H
