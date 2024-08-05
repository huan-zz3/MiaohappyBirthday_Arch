#ifndef IWIFICONTROL_H
#define IWIFICONTROL_H

#include <QObject>
#include <QList>
#include <QMap>

class IWIFIControl : public QObject
{
    Q_OBJECT
public:
    explicit IWIFIControl(QObject *parent = nullptr):QObject(parent){};
    virtual QList<QMap<QString,QString>> getWIFIlist() = 0;
    virtual bool isConnected() = 0;
    virtual bool connectWIFI(QString _name) = 0;
    virtual bool disconnectWIFI() = 0;
    
    
signals:
    
};

#endif // IWIFICONTROL_H
