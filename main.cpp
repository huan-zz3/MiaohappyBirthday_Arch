#include <QApplication>

#include "applicationcore.h"
#include "qweather.h"
#include "l_hxhwebapi.h"
#include "he_ld2410b.h"
#include "ui_home.h"
#include "td_localhost.h"
#include "wifipannel.h"

#include "wifiwpa_package.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    ApplicationCore *apc = new ApplicationCore();
    apc->setWeatherinfoobject(new QWeather(apc));
    apc->setLocationobject(new L_HxhWebAPI(apc));
    apc->testLocation();
    apc->setHumanExistobject(new HE_LD2410B(apc));
    apc->setHomeGUI(new UI_Home());
    apc->setTimeDateobject(new TD_LocalHost(apc));
    apc->testTimeDate();
    
//    WIFIwpa_package wpa;
//    wpa.connectWIFI("Huanzze", "whl369258147");
    apc->setWIFIGUIobject(new WIFIPannel(), new WIFIwpa_package());
    apc->testWIFIpannel();
    
    apc->finishInitObject();
    system("xset dpms 0 0 0");
    return a.exec();
}
