#ifndef APPLICATIONCORE_H
#define APPLICATIONCORE_H

#include <QObject>
#include <QDebug>

#include "ihomegui.h"
#include "ihumanexist.h"
#include "ilocation.h"
#include "itimedate.h"
#include "iweatherinfo.h"
#include "iwifigui.h"

class ApplicationCore : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationCore(QObject *parent = nullptr);
    
    void setHumanExistobject(IHumanExist*);
    void setWeatherinfoobject(IWeatherinfo*);
    void setTimeDateobject(ITimeDate*);
    void setLocationobject(ILocation*);
    void setWIFIGUIobject(IWIFIGUI*);
    void setHomeGUI(IHomeGUI*);
    
    void testLocation();
    
    
private:
    IHumanExist *humanexist_;
    IWeatherinfo *weather_;
    ITimeDate *td_;
    ILocation *lc_;
    IHomeGUI *home_;
    IWIFIGUI *wifigui_;
    
    
    
    
signals:
    
};

#endif // APPLICATIONCORE_H
