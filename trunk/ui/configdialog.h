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

/**
 * @brief Configuration dialog.
 */
class ConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigDialog(QWidget *parent = 0);

protected:
    /**
     * @brief Show event
     */
    virtual void showEvent(QShowEvent *);

private slots:
    /**
     * @brief Accept button pressed.
     */
    void accepted();
    /**
     * @brief Apply button pressed.
     */
    void applied();
    /**
     * @brief Reject button pressed.
     */
    void rejected();

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
    QTabWidget          *tabs;

    GeneralConfigWidget *generalConf;
    ChatConfigWidget    *chatConf;
    ProxyConfigWidget   *proxyConf;
};

#endif // CONFIGDIALOG_H
