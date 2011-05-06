/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef GENERALCONFIGWIDGET_H
#define GENERALCONFIGWIDGET_H

#include <QWidget>

class QComboBox;
class QLabel;

/**
 * @brief General configuration section in configuration dialog.
 */
class GeneralConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralConfigWidget(QWidget *parent = 0);

public slots:
    /**
     * @brief Load configuration from file.
     */
    void load();
    /**
     * @brief Save configuration from file.
     */
    void save();

private:
    /**
     * @brief Creating widgets.
     */
    void createElements();
    /**
     * @brief Layout widgets.
     */
    void layoutElements();

    QComboBox *lang;
    QComboBox *style;
};

#endif // GENERALCONFIGWIDGET_H
