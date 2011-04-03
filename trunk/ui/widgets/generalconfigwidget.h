/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef GENERALCONFIGWIDGET_H
#define GENERALCONFIGWIDGET_H

#include <QWidget>

class QComboBox;
class QLabel;
class QSvgWidget;

class GeneralConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralConfigWidget(QWidget *parent = 0);

    void load();
    void save();

signals:

public slots:
private:
    void createElements();
    void layoutElements();

    QSvgWidget *pic;

    QComboBox *lang;
    QComboBox *style;

};

#endif // GENERALCONFIGWIDGET_H
