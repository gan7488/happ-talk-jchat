/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "imwidget.h"
#include "ui_imwidget.h"

IMWidget::IMWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IMWidget)
{
    ui->setupUi(this);
}

IMWidget::~IMWidget()
{
    delete ui;
}
