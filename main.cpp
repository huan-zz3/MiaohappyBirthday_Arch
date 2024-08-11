#include <QApplication>

#include "applicationcore.h"
#include "qweather.h"
#include "l_hxhwebapi.h"
#include "he_ld2410b.h"
#include "ui_home.h"
#include "td_localhost.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    ApplicationCore *apc = new ApplicationCore();
    apc->setWeatherinfoobject(new QWeather(apc));
    apc->setLocationobject(new L_HxhWebAPI(apc));
//    apc->testLocation();
    apc->setHumanExistobject(new HE_LD2410B(apc));
    apc->setHomeGUI(new UI_Home());
    apc->setTimeDateobject(new TD_LocalHost(apc));
//    apc->testTimeDate();
    
    apc->finishInitObject();
    return a.exec();
}
