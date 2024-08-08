#ifndef QWEATHER_H
#define QWEATHER_H

#include "iweatherinfo.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop> // 用于同步等待响应
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QThread>
#include <QReadWriteLock>
#define days 3
#define Today 0
#define Tomorrow 1
#define ThirdDay 2

static struct DayInformation{
    QString updateTime;
    QString fxDate;
    QString sunrise;
    QString sunset;
    QString moonrise;
    QString moonset;
    QString moonPhase;
    QString moonPhaseIcon;
    QString tempMax;
    QString tempMin;
    QString iconDay;
    QString textDay;
    QString iconNight;
    QString textNight;
    QString wind360Day;
    QString windDirDay;
    QString windScaleDay;
    QString windSpeedDay;
    QString wind360Night;
    QString windDirNight;
    QString windScaleNight;
    QString windSpeedNight;
    QString humidity;
    QString precip;
    QString pressure;
    QString vis;
    QString cloud;
    QString uvIndex;
    friend QDebug& operator<<(QDebug out, const DayInformation& info)
        {
            out << info.updateTime << info.fxDate << info.sunrise << info.iconDay;
            return out;
        }
}dayInformation[days];
static QDateTime dt;
static QString city;
static QString temperaturenow;
static QReadWriteLock rwLock_dt, rwLock_dI;


/**
 * @brief The QweatherAPIService class
 * It is a weatherAPI and Time server class, use 和风天气 as cloudAPI server. Developer should'n instance this class, and should keep the class single.
 */
class QweatherAPIService : public QObject
{
    Q_OBJECT
public:
    explicit QweatherAPIService(QObject *parent = nullptr);
    ~QweatherAPIService();
    
    
private:
    QTimer *timer_weather, *timer_time;
    QString locationID;
    
    
    void analyzeWeatherData(QByteArray);
    void analyzeCityData(QByteArray);
    void analyzelocationID(QByteArray);
    void analyzeWeathernowData(QByteArray);
//    void analyzeTimedateData(QByteArray);// abort
    QString getCityEnglishName(const QString &chineseCityName);
    
public slots:
    void startService(){
        if(!timer_weather->isActive()){
            slot_updateAPIcity();
            slot_updateAPIlocationid();
            slot_updateAPIweather();
            slot_updateAPIweathernow();
            connect(timer_weather, &QTimer::timeout, this, &QweatherAPIService::slot_updateAPIcity, Qt::QueuedConnection);
            connect(timer_weather, &QTimer::timeout, this, &QweatherAPIService::slot_updateAPIlocationid, Qt::QueuedConnection);
            connect(timer_weather, &QTimer::timeout, this, &QweatherAPIService::slot_updateAPIweather, Qt::QueuedConnection);
            connect(timer_weather, &QTimer::timeout, this, &QweatherAPIService::slot_updateAPIweathernow, Qt::QueuedConnection);
            timer_weather->start(10*60*1000); // 10mins
        }
        if(!timer_time->isActive()){
            slot_updatedt();
            connect(timer_time, &QTimer::timeout, this, &QweatherAPIService::slot_updatedt, Qt::QueuedConnection);
            timer_time->start(1000);
        }
    }
    void stopService(){
        timer_weather->stop();
        disconnect(timer_weather,0,0,0);
        timer_time->stop();
        disconnect(timer_time,0,0,0);
        
        this->deleteLater();
    }
    
private slots:
    void slot_updateAPIcity();
    void slot_updateAPIlocationid();
    void slot_updateAPIweather();
    void slot_updateAPIweathernow();
    
//    void slot_getAPItimedate();// abort
    void slot_updatedt();
    
signals:
    
};

class QWeather : public IWeatherinfo
{
    Q_OBJECT
public:
    explicit QWeather(QObject *parent = nullptr);
    
public:// override
    QString getTodayIcon() override;
    QString getTomorrowIcon() override;
    QString getThirdayIcon() override;
    QString getNowTemp() override;
    QString getTodayMaxTemp() override;
    QString getTodayMinTemp() override;
    QString getTomorrowMaxTemp() override;
    QString getTomorrowMinTemp() override;
    QString getThirdayMaxTemp() override;
    QString getThirdayMinTemp() override;
    
private:
    QweatherAPIService *qWA;
    void InitQWeatherAPIService();
    
signals:
    
};

#endif // QWEATHER_H
