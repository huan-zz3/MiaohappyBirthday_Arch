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

namespace Ui {
class WIFIPannel;
}

class WIFIPannel : public IWIFIGUI
{
    Q_OBJECT
    
public:
    explicit WIFIPannel(QWidget *parent = nullptr);
    ~WIFIPannel();
    
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
    QString loadFont(QString fontpath);
    
private slots:
    void slot_connectThiswifi(QTableWidgetItem *);
};

#endif // WIFIPANNEL_H
