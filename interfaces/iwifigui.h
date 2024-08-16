#ifndef IWIFIGUI_H
#define IWIFIGUI_H

#include <QObject>
#include <QWidget>
#include "iwificontrol.h"

class IWIFIGUI : public QWidget
{
    Q_OBJECT
public:
    explicit IWIFIGUI(QWidget *parent = nullptr):QWidget(parent){};
    
    virtual void setWIFIControl(IWIFIControl *) = 0;
    virtual void showWIFIPanel() = 0;
    virtual void closeWIFIPanel() = 0;
    virtual void addWIFIItem() = 0;
    
protected:
    IWIFIControl *wfc;
    
signals:
    
};

#endif // IWIFIGUI_H
