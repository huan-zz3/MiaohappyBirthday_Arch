#ifndef WIFIWPA_PACKAGE_H
#define WIFIWPA_PACKAGE_H

#include <QObject>
#include <iostream>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QProcess>

#include <cstring>
#include <string>
#include <chrono>
#include <thread>

#include "iwificontrol.h"
#include "wpa_ctrl.h"

class WIFIwpa_package : public IWIFIControl
{
    Q_OBJECT
public:
    explicit WIFIwpa_package(QObject *parent = nullptr);
    
    QList<QMap<QString,QString>> getWIFIlist() override;
    bool isConnected() override;
    bool connectWIFI(QString _name, QString _password) override;
    bool disconnectWIFI() override;
    
private:
    struct wpa_ctrl *ctrl;
    bool isInterfaceOpened = false;
    void openControlInterface();
    void replaceHexChar(QString *);
    bool runDhclient();
    
signals:
    
};

#endif // WIFIWPA_PACKAGE_H
