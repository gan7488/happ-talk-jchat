/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef TALKWIDGET_H
#define TALKWIDGET_H

#include <QWidget>

class QTextEdit;
class QPushButton;
class QWidget;

class TalkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TalkWidget(QWidget *parent = 0, QWidget *info = 0);

signals:

public slots:

private:
    void createTexts();
    void createButtons();
    void layoutElements();

    QTextEdit *story;
    QTextEdit *message;

    QPushButton *send;

    QPushButton *bold;
    QPushButton *italic;
    QPushButton *underline;
    QPushButton *strikeout;

    QPushButton *fontSize;

    QPushButton *clear;

    QWidget *info;

private slots:

};

#endif // TALKWIDGET_H
