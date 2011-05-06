/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef PROXYCONFIGWIDGET_H
#define PROXYCONFIGWIDGET_H

#include <QWidget>

class QComboBox;
class QLineEdit;

/**
 * @brief Proxy configuration section in configaration dialog.
 */
class ProxyConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProxyConfigWidget(QWidget *parent = 0);

public slots:
    /**
     * @brief Load configuration from file.
     */
    void load();
    /**
     * @brief Save configuration from file.
     */
    void save();

private slots:
    void proxyTypeChanged ( int index );

private:
    /**
     * @brief Creating widgets.
     */
    void createElements();
    /**
     * @brief Layout widgets.
     */
    void layoutElements();

    QComboBox *proxyType;

    QLineEdit *proxyHost;
    QLineEdit *proxyPort;
    QLineEdit *proxyUser;
    QLineEdit *proxyPass;
};

#endif // PROXYCONFIGWIDGET_H
