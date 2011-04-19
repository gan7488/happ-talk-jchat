/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QTextEdit;

/*
 About dialog.
 */
class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);

private slots:
    /*
     Slots
     */
    void helpRequested();

private:
    /*
     Setup UI
     */
    void createElements();
    void layoutElements();

    /*
     Elements
     */
    QDialogButtonBox    *buttons;
    QTextEdit           *about;
};

#endif // ABOUTDIALOG_H
