/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QTextEdit;

/**
 * @brief About dialog.
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
    /**
     * @brief Creating widgets.
     */
    void createElements();
    /**
     * @brief Layout widgets.
     */
    void layoutElements();

    /*
     Elements
     */
    QDialogButtonBox    *buttons;
    QTextEdit           *about;
};

#endif // ABOUTDIALOG_H
