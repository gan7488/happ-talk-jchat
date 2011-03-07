/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QTabWidget;
class GeneralConfigWidget;
class ChatConfigWidget;
class ProxyConfigWidget;

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

    GeneralConfigWidget *generalConf;
    ChatConfigWidget *chatConf;
    ProxyConfigWidget *proxyConf;

private slots:
    void accepted();
    void applied();
    void rejected();
};

#endif // CONFIGDIALOG_H
