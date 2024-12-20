#ifndef APPLICATIONCORE_H
#define APPLICATIONCORE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QEventLoop>
#include <QProcess>

#include "ihomegui.h"
#include "ihumanexist.h"
#include "ilocation.h"
#include "itimedate.h"
#include "iweatherinfo.h"
#include "iwifigui.h"
#include "iwificontrol.h"
#include "IWallpaper.h"

class ApplicationCore : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationCore(QObject *parent = nullptr);
    void finishInitObject();
    
    void setHumanExistobject(IHumanExist*);
    void setWeatherinfoobject(IWeatherinfo*);
    void setTimeDateobject(ITimeDate*);
    void setLocationobject(ILocation*);
    void setWIFIGUIobject(IWIFIGUI*, IWIFIControl*);
    void setHomeGUI(IHomeGUI*);
    void setWallpaperGUI(IWallpaper*);
    
    void testLocation();
    void testTimeDate();
    void testWIFIpannel();
    void testWallpaper();
    
    
private:
    IHumanExist *humanexist_;
    IWeatherinfo *weather_;
    ITimeDate *td_;
    ILocation *lc_;
    IHomeGUI *home_;
    IWIFIGUI *wifigui_;
    IWallpaper *wallpaper_;
    
    QTimer *timer_time, *timer_weatherinfo, *timer_location;
    
    
    void initTimerinUpdatetime();
    void virtualKeyBoard();
    
private slots:
    void slot_UpdateTime();
    void slot_UpdateWeatherInfo();
    void slot_UpdateLocation();
    void slot_MenuPress();
    void slot_RestartPress();
    void slot_HumanExist();
    void slot_HumanNotExist();
    
signals:
    
};

#endif // APPLICATIONCORE_H
