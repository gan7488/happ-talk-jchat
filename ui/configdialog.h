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

/*
 Configuration dialog
 */
class ConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigDialog(QWidget *parent = 0);

protected:
    /*
     Show event
     */
    virtual void showEvent(QShowEvent *);

private slots:
    /*
     Slots
     */
    void accepted();
    void applied();
    void rejected();

private:
    /*
     Setup UI
     */
    void createElements();
    void layoutElements();
    void createButtons();
    void createTabs();

    /*
     Elements
     */
    QDialogButtonBox    *buttons;
    QTabWidget          *tabs;

    GeneralConfigWidget *generalConf;
    ChatConfigWidget    *chatConf;
    ProxyConfigWidget   *proxyConf;
};

#endif // CONFIGDIALOG_H
