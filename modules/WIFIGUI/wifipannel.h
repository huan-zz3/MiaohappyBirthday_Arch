#ifndef WIFIPANNEL_H
#define WIFIPANNEL_H

#include <QWidget>
#include "iwifigui.h"
#include "iwificontrol.h"
#include "wifipassworddialog.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QPushButton>
#include <QSettings>
#include <QVariant>

namespace Ui {
class WIFIPannel;
}

class WIFIPannel : public IWIFIGUI
{
    Q_OBJECT
    
public:
    explicit WIFIPannel(QWidget *parent = nullptr);
    ~WIFIPannel();
    
    void setDefaultWIFI() override;
    void setWIFIControl(IWIFIControl *) override;
    void showWIFIPanel() override;
    void closeWIFIPanel() override;
    void addWIFIItem() override;
    
    
private:
    Ui::WIFIPannel *ui;
    QTableWidget *tablewidget;
    QTableWidgetItem *item_singlewifi, *item_ssid, *item_signalLevel;
    WifiPasswordDialog *passworddialog;
    QPushButton *backbutton;
    
    void initTable();
    void initButton();
    void initdefaultWIFI();
    QString loadFont(QString fontpath);
    void saveData(const QString &key, const QVariant &value);
    QVariant loadData(const QString &key, const QVariant &defaultValue);
    
private slots:
    void slot_connectThiswifi(QTableWidgetItem *);
};

#endif // WIFIPANNEL_H
