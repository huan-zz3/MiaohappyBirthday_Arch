#include <QApplication>

#include "applicationcore.h"
#include "qweather.h"
#include "l_hxhwebapi.h"
#include "he_ld2410b.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    ApplicationCore *apc = new ApplicationCore();
//    apc->setWeatherinfoobject(new QWeather(apc));
    apc->setLocationobject(new L_HxhWebAPI(apc));
    apc->testLocation();
    apc->setHumanExistobject(new HE_LD2410B(apc));
    
    return a.exec();
}
