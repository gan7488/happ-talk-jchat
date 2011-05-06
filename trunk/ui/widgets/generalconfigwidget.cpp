/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "generalconfigwidget.h"
#include <QtGui>
#include <QSvgWidget>

/*
 Constructors
 */
GeneralConfigWidget::GeneralConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWhatsThis(tr("General configuration. Choose your language,<br>"
                          "Select theme pack and other cool things"));

    createElements();
    layoutElements();
}

/*
 Setup UI
 */
void GeneralConfigWidget::createElements()
{
    lang    = new QComboBox();
    lang->addItem(tr("Default - English"));
    //lang->addItem(tr("Russian"));
    lang->setFixedWidth(150);

    style   = new QComboBox();
    style->addItem(tr("Default"));
    //style->addItem(tr("..."));
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

    QSvgWidget *pic = new QSvgWidget(":/images/desktop.svg");
    pic->setFixedSize(100,100);

    hLayout->addWidget(pic);

    this->setLayout(hLayout);
}

/*
 Slots
 */
void GeneralConfigWidget::load() { }

void GeneralConfigWidget::save() { }
