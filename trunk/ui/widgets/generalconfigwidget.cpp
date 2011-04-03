/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "generalconfigwidget.h"
#include <QtGui>
#include <QSvgWidget>

GeneralConfigWidget::GeneralConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    createElements();
    layoutElements();
}

void GeneralConfigWidget::load()
{

}

void GeneralConfigWidget::save()
{

}
void GeneralConfigWidget::createElements()
{
    pic = new QSvgWidget(":/images/desktop.svg");
    pic->setFixedSize(100,100);

    lang    = new QComboBox();
    lang->setFixedWidth(150);
    style   = new QComboBox();
    style->setFixedWidth(150);
}
void GeneralConfigWidget::layoutElements()
{
    QFormLayout *fLayout = new QFormLayout();
    fLayout->addRow(tr("Language:"), lang);
    fLayout->addRow(tr("Style:"), style);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addLayout(fLayout);
    hLayout->addStretch();
    hLayout->addWidget(pic);

    this->setLayout(hLayout);
}
