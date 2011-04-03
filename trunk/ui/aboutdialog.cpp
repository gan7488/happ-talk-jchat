/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "aboutdialog.h"
#include "consts.h"
#include <QtGui>
#include <QtSvg/QSvgWidget>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle(tr("About programm"));
    this->setFixedSize(400, 200);
    this->setWindowIcon(QIcon(":/images/info.svg"));

    createElements();
    layoutElements();
}

void AboutDialog::createElements()
{
    about = new QTextEdit();
    about->setReadOnly(true);
    int maj = (version >> 20) & 0xFF;
    int min = (version >> 12) & 0xFF;
    int build = version & 0xFFF;
    about->setHtml(tr("<h2>%1 %2.%3.%4</h2>"
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
                       "<li>Denzel</li></ul>").arg(app).arg(maj).arg(min).arg(build));

    buttons = new QDialogButtonBox(Qt::Horizontal);
    buttons->addButton(tr("Help"), QDialogButtonBox::HelpRole);
    buttons->addButton(tr("Close"), QDialogButtonBox::AcceptRole);

    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttons, SIGNAL(helpRequested()), this, SLOT(helpRequested()));

    logo = new QSvgWidget();
    logo->setFixedSize(130,150);
    logo->load(QString(":/images/logo.svg"));
}

void AboutDialog::layoutElements()
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(logo);
    hLayout->addWidget(about);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout);
    vLayout->addSpacing(10);
    vLayout->addWidget(buttons);

    setLayout(vLayout);
}

void AboutDialog::helpRequested()
{
    QDesktopServices::openUrl(QUrl(url));
}
