#include "applicationcore.h"

ApplicationCore::ApplicationCore(QObject *parent) : QObject(parent)
{
    
}

void ApplicationCore::setHumanExistobject(IHumanExist* _ih){
    humanexist_ = _ih;
}
void ApplicationCore::setWeatherinfoobject(IWeatherinfo* _iw){
   weather_ = _iw;
}
void ApplicationCore::setTimeDateobject(ITimeDate* _it){
    td_ = _it;
}
void ApplicationCore::setLocationobject(ILocation* _il){
    lc_ = _il;
}
void ApplicationCore::setWIFIGUIobject(IWIFIGUI* _iw){
    wifigui_ = _iw;
}
void ApplicationCore::setHomeGUI(IHomeGUI* _ih){
    home_ = _ih;
}


void ApplicationCore::testLocation(){
    qDebug()<<lc_->getNowLocation();
    
}
