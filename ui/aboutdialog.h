/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QSvgWidget;
class QTextEdit;

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);

private:
    void createElements();
    void layoutElements();

    QDialogButtonBox    *buttons;
    QSvgWidget          *logo;
    QTextEdit           *about;

private slots:
    void helpRequested();
};

#endif // ABOUTDIALOG_H
