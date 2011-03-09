/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "generalconfigwidget.h"
#include <QtGui>

GeneralConfigWidget::GeneralConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(new QLabel("GENERAL SETTINGS GOES HERE"));
    this->setLayout(hLayout);
}
