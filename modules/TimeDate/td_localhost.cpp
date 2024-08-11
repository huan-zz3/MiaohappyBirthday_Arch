#include "td_localhost.h"

TD_LocalHost::TD_LocalHost(QObject *parent) : ITimeDate(parent)
{
    
}
TD_LocalHost::~TD_LocalHost(){
    
}
QString TD_LocalHost::getNowTime(){
    return QDateTime::currentDateTime().time().toString(TIMEFORMAT);
}
QString TD_LocalHost::getTodayDate(){
    return QDateTime::currentDateTime().date().toString(DATEFORMAT);
}
QString TD_LocalHost::getTodayWeek(){
    int dayOfWeek = QDateTime::currentDateTime().date().dayOfWeek();
    if(dayOfWeek - 1 >= 7){
        dayOfWeek = dayOfWeek - 1 -7;
    }else{
        dayOfWeek = dayOfWeek - 1;
    }
    QString daysOfWeek[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    QString dayOfWeekStr = daysOfWeek[dayOfWeek];
    return dayOfWeekStr;
}
QString TD_LocalHost::getTomorrowWeek(){
    int dayOfWeek = QDateTime::currentDateTime().date().dayOfWeek();
    if(dayOfWeek - 1 + 1 >= 7){
        dayOfWeek = dayOfWeek - 1 + 1 -7;
    }else{
        dayOfWeek = dayOfWeek - 1 + 1;
    }
    QString daysOfWeek[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    QString dayOfWeekStr = daysOfWeek[dayOfWeek];
    return dayOfWeekStr;
}
QString TD_LocalHost::getThirdayWeek(){
    int dayOfWeek = QDateTime::currentDateTime().date().dayOfWeek();
    if(dayOfWeek - 1 + 2 >= 7){
        dayOfWeek = dayOfWeek - 1 + 2 -7;
    }else{
        dayOfWeek = dayOfWeek - 1 + 2;
    }
    QString daysOfWeek[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    QString dayOfWeekStr = daysOfWeek[dayOfWeek];
    return dayOfWeekStr;
}
