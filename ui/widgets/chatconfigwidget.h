/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef CHATCONFIGWIDGET_H
#define CHATCONFIGWIDGET_H

#include <QWidget>

/**
 * @brief Chat configuration section in configuration dialog.
 */
class ChatConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatConfigWidget(QWidget *parent = 0);

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
};

#endif // CHATCONFIGWIDGET_H
