/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "talkwidget.h"
#include <QtGui>

TalkWidget::TalkWidget(QWidget *parent, QWidget *info) :
    QWidget(parent)
{
    this->info = info;
    if (info != 0)
    {
        info->setFixedWidth(100);
    }

    createTexts();
    createButtons();
    layoutElements();
}

void TalkWidget::createTexts()
{
    story = new QTextEdit();
    story->setReadOnly(true);

    message = new QTextEdit();
    message->setFixedHeight(70);
}

void TalkWidget::createButtons()
{
    bold = new QPushButton(tr("B"));
    bold->setCheckable(true);
    bold->setFixedSize(25, 25);

    italic = new QPushButton(tr("I"));
    italic->setCheckable(true);
    italic->setFixedSize(25, 25);

    underline = new QPushButton(tr("U"));
    underline->setCheckable(true);
    underline->setFixedSize(25, 25);

    strikeout = new QPushButton(tr("-"));
    strikeout->setCheckable(true);
    strikeout->setFixedSize(25,25);

    fontSize = new QPushButton("Size");
    fontSize->setFixedSize(60, 25);

    clear = new QPushButton(tr("Clear"));
    clear->setFixedSize(40, 25);

    send = new QPushButton(tr("Send"));
    send->setFixedSize(40, 70);
}

void TalkWidget::layoutElements()
{
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(bold);
    hLayout1->addWidget(italic);
    hLayout1->addWidget(underline);
    hLayout1->addWidget(strikeout);
    hLayout1->addSpacing(5);
    hLayout1->addWidget(fontSize);
    hLayout1->addSpacing(5);
    hLayout1->addWidget(clear);
    hLayout1->addStretch();

    QHBoxLayout *hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(message);
    hLayout2->addWidget(send);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(story);
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);

    if (info == 0)
    {
        this->setLayout(vLayout);
        return;
    }

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addLayout(vLayout);
    layout->addWidget(info);
    this->setLayout(layout);
}


