/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "proxyconfigwidget.h"
#include <QtGui>

ProxyConfigWidget::ProxyConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(new QLabel("PROXIES SETTINGS GOES HERE"));
    this->setLayout(hLayout);
}
