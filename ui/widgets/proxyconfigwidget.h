/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef PROXYCONFIGWIDGET_H
#define PROXYCONFIGWIDGET_H

#include <QWidget>

class QComboBox;
class QLineEdit;

/*
 Configaration dialog. Proxy configuration section.
 */
class ProxyConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProxyConfigWidget(QWidget *parent = 0);

public slots:
    /*
     Slots
     */
    void load();
    void save();

private slots:
    void proxyTypeChanged ( int index );

private:
    /*
     Setup UI
     */
    void createElements();
    void layoutElements();

    /*
     Elements
     */
    QComboBox *proxyType;

    QLineEdit *proxyHost;
    QLineEdit *proxyPort;
    QLineEdit *proxyUser;
    QLineEdit *proxyPass;
};

#endif // PROXYCONFIGWIDGET_H
