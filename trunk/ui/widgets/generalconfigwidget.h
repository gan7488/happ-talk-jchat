/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef GENERALCONFIGWIDGET_H
#define GENERALCONFIGWIDGET_H

#include <QWidget>

class QComboBox;
class QLabel;

/*
 Configuration dialog. General configuration section.
 */
class GeneralConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralConfigWidget(QWidget *parent = 0);

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
    QComboBox *lang;
    QComboBox *style;
};

#endif // GENERALCONFIGWIDGET_H
