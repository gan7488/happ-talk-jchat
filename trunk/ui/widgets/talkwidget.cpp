/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "talkwidget.h"
#include "messagewidget.h"
#include <QtGui>

TalkWidget::TalkWidget(QWidget *parent, QWidget *info) :
    QWidget(parent)
{
    this->info = info;

    createElements();
    layoutElements();
}

void TalkWidget::messageReceived(const QString &msg)
{
    if (!msg.isNull() && !msg.isEmpty())
    story->append(QString("(%1)%2: %3").arg(QTime::currentTime().toString()).arg(QString::fromStdString(m_jid.username())).arg(msg));
}

void TalkWidget::sendMessage()
{
    story->append(QString("(%1)I: %2").arg(QTime::currentTime().toString()).arg(message->toPlainText()));
    emit sendMessage(m_jid, message->toPlainText());
    message->clear();
}

void TalkWidget::createElements()
{
    story = new QTextEdit();
    story->setReadOnly(true);

    message = new MessageWidget();
    message->setFixedHeight(70);
    connect(message, SIGNAL(accepted()), this, SLOT(sendMessage()));

    bold = new QPushButton(tr("B"));
    bold->setEnabled(false);
    bold->setCheckable(true);
    bold->setFixedSize(25, 25);

    italic = new QPushButton(tr("I"));
    italic->setEnabled(false);
    italic->setCheckable(true);
    italic->setFixedSize(25, 25);

    underline = new QPushButton(tr("U"));
    underline->setEnabled(false);
    underline->setCheckable(true);
    underline->setFixedSize(25, 25);

    strikeout = new QPushButton(tr("-"));
    strikeout->setEnabled(false);
    strikeout->setCheckable(true);
    strikeout->setFixedSize(25,25);

    fontSize = new QPushButton("Size");
    fontSize->setEnabled(false);
    fontSize->setFixedSize(60, 25);

    send = new QPushButton(tr("Send"));
    send->setFixedSize(70, 70);
    connect(send, SIGNAL(clicked()), this, SLOT(sendMessage()));
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
    layout->addLayout(vLayout, 4);
    layout->addWidget(info, 1);
    this->setLayout(layout);
}


