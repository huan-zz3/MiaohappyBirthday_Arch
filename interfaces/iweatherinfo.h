#ifndef IWEATHERINFO_H
#define IWEATHERINFO_H

#include <QObject>
#include <QString>

class IWeatherinfo : public QObject
{
    Q_OBJECT
public:
    explicit IWeatherinfo(QObject *parent = nullptr):QObject(parent){};
    virtual QString getTodayIcon() = 0;
    virtual QString getTomorrowIcon() = 0;
    virtual QString getThirdayIcon() = 0;
    virtual QString getNowTemp() = 0;
    virtual QString getTodayMaxTemp() = 0;
    virtual QString getTodayMinTemp() = 0;
    virtual QString getTomorrowMaxTemp() = 0;
    virtual QString getTomorrowMinTemp() = 0;
    virtual QString getThirdayMaxTemp() = 0;
    virtual QString getThirdayMinTemp() = 0;
    
signals:
    
};

#endif // IWEATHERINFO_H
