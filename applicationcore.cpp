#include "applicationcore.h"

ApplicationCore::ApplicationCore(QObject *parent) : QObject(parent)
{
    initTimerinUpdatetime();
    virtualKeyBoard();
}
void ApplicationCore::finishInitObject(){
    timer_time->start(500);
    timer_weatherinfo->start(1000);
    timer_location->start(1000*60*3);
    
    connect(home_, &IHomeGUI::signal_MenuPress, this, &ApplicationCore::slot_MenuPress);
    connect(home_, &IHomeGUI::signal_RestartPress, this, &ApplicationCore::slot_RestartPress);
    connect(humanexist_, &IHumanExist::signal_HumanExist, this, &ApplicationCore::slot_HumanExist, Qt::QueuedConnection);
    connect(humanexist_, &IHumanExist::signal_HumanNotExist, this, &ApplicationCore::slot_HumanNotExist, Qt::QueuedConnection);
    
    home_->setNowLocation(lc_->getNowLocation());// first exec
    home_->showHomeForm();
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
void ApplicationCore::setWIFIGUIobject(IWIFIGUI* _iw, IWIFIControl* _iwc){
    wifigui_ = _iw;
    wifigui_->setWIFIControl(_iwc);
    wifigui_->setDefaultWIFI();
}
void ApplicationCore::setHomeGUI(IHomeGUI* _ih){
    home_ = _ih;
}
void ApplicationCore::setWallpaperGUI(IWallpaper* _wp){
    wallpaper_ = _wp;
}
void ApplicationCore::testLocation(){
    qDebug()<<lc_->getNowLocation();
    
}
void ApplicationCore::testTimeDate(){
    qDebug()<<td_->getNowTime();
    qDebug()<<td_->getTodayDate();
    qDebug()<<td_->getTodayWeek();
}
void ApplicationCore::initTimerinUpdatetime(){
    timer_time = new QTimer(this);
    connect(timer_time, &QTimer::timeout, this, &ApplicationCore::slot_UpdateTime);
    
    qDebug()<<"<initTimerinUpdatetime>";
    
    timer_weatherinfo = new QTimer(this);
    connect(timer_weatherinfo, &QTimer::timeout, this, &ApplicationCore::slot_UpdateWeatherInfo);
    
    timer_location = new QTimer(this);
    connect(timer_location, &QTimer::timeout, this, &ApplicationCore::slot_UpdateLocation);
    
}
void ApplicationCore::virtualKeyBoard(){
    system("onboard &");
}
void ApplicationCore::slot_UpdateTime(){
    qDebug()<<"<slot_UpdateTime>";
    home_->setNowTime(td_->getNowTime());
    home_->setTodayDate(td_->getTodayDate());
    home_->setTodayWeek(td_->getTodayWeek());
    home_->setTomorrowWeek(td_->getTomorrowWeek());
    home_->setThirdayWeek(td_->getThirdayWeek());
}
void ApplicationCore::slot_UpdateWeatherInfo(){
    qDebug()<<"<slot_UpdateWeatherInfo>";
    home_->setNowTemp(weather_->getNowTemp());
    home_->setTodayMaxTemp(weather_->getTodayMaxTemp());
    home_->setTodayMinTemp(weather_->getTodayMinTemp());
    home_->setTomorrowMaxTemp(weather_->getTomorrowMaxTemp());
    home_->setTomorrowMinTemp(weather_->getTomorrowMinTemp());
    home_->setThirdayMaxTemp(weather_->getThirdayMaxTemp());
    home_->setThirdayMinTemp(weather_->getThirdayMinTemp());
    
    home_->setTodayIcon(weather_->getTodayIcon());
    home_->setTomorrowIcon(weather_->getTomorrowIcon());
    home_->setThirdayIcon(weather_->getThirdayIcon());
    
}
void ApplicationCore::slot_UpdateLocation(){
    home_->setNowLocation(lc_->getNowLocation());
}
void ApplicationCore::testWIFIpannel(){
    wifigui_->addWIFIItem();
}
void ApplicationCore::slot_MenuPress(){
    wifigui_->showWIFIPanel();
}
void ApplicationCore::slot_RestartPress(){
    system("reboot");
}
void ApplicationCore::testWallpaper(){
    wallpaper_->showWallpaperForm();
//    wallpaper_->nextPicture();
//    QEventLoop loop;
//    QTimer timer;
//    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
//    timer.start(3000);
//    loop.exec();
//    wallpaper_->nextPicture();
}
void ApplicationCore::slot_HumanExist(){
    home_->showHomeForm();
    wallpaper_->closeWallpaperForm();
}
void ApplicationCore::slot_HumanNotExist(){
    wallpaper_->showWallpaperForm();
    home_->closeHomeForm();
}
