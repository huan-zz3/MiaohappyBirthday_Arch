#ifndef IWIFIGUI_H
#define IWIFIGUI_H

#include <QObject>

class IWIFIGUI : public QObject
{
    Q_OBJECT
public:
    explicit IWIFIGUI(QObject *parent = nullptr):QObject(parent){};
    virtual void showWIFIPanel() = 0;
    virtual void closeWIFIPanel() = 0;
    
    
    
signals:
    
};

#endif // IWIFIGUI_H
