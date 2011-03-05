/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class QTextEdit;
class QDialogButtonBox;
class QSvgWidget;

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);

private:
    void createElements();
    void fillContent();

private slots:
    void accepted();
    void helpRequested();

private:
    QTextEdit *text;
    QDialogButtonBox *buttonBox;
    QSvgWidget *logo;

};

#endif // ABOUTDIALOG_H
