/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QTabWidget;

class ConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigDialog(QWidget *parent = 0);

signals:

public slots:

private:
    void createTabs();
    void createButtons();
    void layoutElements();

    QDialogButtonBox *buttonBox;
    QTabWidget *tabs;

private slots:
    void accepted();
    void applied();
    void rejected();
};

#endif // CONFIGDIALOG_H
