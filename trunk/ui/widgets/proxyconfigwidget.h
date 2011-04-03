/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef PROXYCONFIGWIDGET_H
#define PROXYCONFIGWIDGET_H

#include <QWidget>

class QComboBox;
class QFormLayout;
class QLineEdit;
class QSvgWidget;

class ProxyConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProxyConfigWidget(QWidget *parent = 0);


    void load();
    void save();
signals:

public slots:
private:
    void createElements();
    void layoutElements();

    QComboBox *proxyType;

    QFormLayout *proxyConf;

    QLineEdit *proxyHost;
    QLineEdit *proxyPort;
    QLineEdit *proxyUser;
    QLineEdit *proxyPass;

    QSvgWidget *pic;
private slots:
    void proxyTypeChanged ( int index );

};

#endif // PROXYCONFIGWIDGET_H
