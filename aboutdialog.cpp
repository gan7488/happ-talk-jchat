/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "aboutdialog.h"
#include <QtGui>
#include <QtSvg/QSvgWidget>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setFixedSize(600, 300);
    createElements();
    fillContent();
}

void AboutDialog::createElements()
{
    text = new QTextEdit();
    text->setReadOnly(true);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(tr("Help"), QDialogButtonBox::HelpRole);
    buttonBox->addButton(tr("Close"), QDialogButtonBox::AcceptRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(helpRequested()), this, SLOT(helpRequested()));

    logo = new QSvgWidget();
    logo->setFixedSize(190,200);
    //TODO FROM RESOURCES
    logo->load(QString("images/logo.svg"));

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(logo);
    hLayout->addWidget(text);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(hLayout);
    layout->addWidget(buttonBox);

    setLayout(layout);
}

void AboutDialog::fillContent()
{
    //TODO HERE
    text->setHtml("<h3>Jchat</h3><h4>Author: Svirskiy Sergey</h4>"
                  "Additional information: blah blah blah");
}

void AboutDialog::accepted()
{
    this->accept();
}

void AboutDialog::helpRequested()
{
    //TODO HERE
}
