/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "aboutdialog.h"
#include <QtGui>
#include <QtSvg/QSvgWidget>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setFixedSize(400, 200);
    createElements();
    layoutElements();
    fillContent();
}

void AboutDialog::createElements()
{
    about = new QTextEdit();
    about->setReadOnly(true);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(tr("Help"), QDialogButtonBox::HelpRole);
    buttonBox->addButton(tr("Close"), QDialogButtonBox::AcceptRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(helpRequested()), this, SLOT(helpRequested()));

    logo = new QSvgWidget();
    logo->setFixedSize(130,150);
    logo->load(QString(":/images/logo.svg"));
}

void AboutDialog::layoutElements()
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(logo);
    hLayout->addWidget(about);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(hLayout);
    layout->addWidget(buttonBox);

    setLayout(layout);
}

void AboutDialog::fillContent()
{
    this->setWindowTitle(tr("About programm"));
    about->setHtml(tr("<h2>Jchat #0 alfa</h2>"
                      "<p style='font-size: 12px;'>Jchat is a messaging client based on libgloox. "
                      "Jchat is written in C++ using Qt. "
                      "Jchat is released, and may be modified and redistributed,  "
                      "under the terms of the Lesser GPL.  "
                      "A copy of the GPL is distributed with Jchat.  "
                      "There is no warranty for Jchat.</p>"
                      "<h3>Authors:</h3>"
                      "<ul style='font-size: 12px;'><li>Svirskiy Sergey</li></ul>"
                      "<h3>Testers:</h3>"
                      "<ul style='font-size: 12px;'><li>DEg</li>"
                      "<li>Un1c0rn</li>"
                      "<li>Denzel</li></ul>"));
}

void AboutDialog::helpRequested()
{
    QDesktopServices::openUrl(QUrl("http://code.google.com/p/happ-talk-jchat/"));
}
