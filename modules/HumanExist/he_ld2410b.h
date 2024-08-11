#ifndef HE_LD2410B_H
#define HE_LD2410B_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QThread>

#include <iostream>
#include <thread>
#include <chrono>

#include "ihumanexist.h"
#include "gpiod.h"

#define INTERRUPT_GPIO 74

class ExistenceofHumanBody;
class HE_LD2410B : public IHumanExist
{
    Q_OBJECT
public:
    HE_LD2410B(QObject *parent = nullptr);
    
    
private:
    ExistenceofHumanBody *eh_;
    
private slots:
    
};


class ExistenceofHumanBody : public QObject
{
    Q_OBJECT
public:
    explicit ExistenceofHumanBody(int, IHumanExist *parent = nullptr);
    
public slots:
    void slot_onThreadStarted();
    
private slots:
    
    
private:
    IHumanExist *IHparent_;
    QThread *newThread;
    int line;
    void gpioInit(int);
    void handle_event(struct gpiod_line_event *);
    
//signals:
//    void signal_pinEdgeChange(int);
    
};

#endif // HE_LD2410B_H
