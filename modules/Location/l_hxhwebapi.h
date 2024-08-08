#ifndef L_HXHWEBAPI_H
#define L_HXHWEBAPI_H

#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QEventLoop>
#include <QFile>

#include "ilocation.h"

class L_HxhWebAPI : public ILocation
{
    Q_OBJECT
public:
    explicit L_HxhWebAPI(QObject *parent = nullptr);
    
    QString getNowLocation() override;
    
private:
    QByteArray getAPICity();
    QString analyzeCityData(const QByteArray &_data);
    QString getCityEnglishName(const QString &_ChineseCityName);
    
signals:
    
};

#endif // L_HXHWEBAPI_H
