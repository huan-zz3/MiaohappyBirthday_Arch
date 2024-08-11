#include "qweather.h"

QweatherAPIService::QweatherAPIService(QObject *parent) : QObject(parent)
{
    timer_weather = new QTimer(this);
    timer_time = new QTimer(this);
    
}
QweatherAPIService::~QweatherAPIService()
{
    timer_weather->deleteLater();
    timer_time->deleteLater();
}


void QweatherAPIService::analyzeWeatherData(QByteArray _data){
    QJsonDocument _doc = QJsonDocument::fromJson(_data);

    QJsonObject _obj = _doc.object();// first key&value
    QJsonValue _value = _obj.value("daily");//value in first key="daily"--(1)
    QJsonArray _array = _value.toArray();// convert (1) to array--(2)
    rwLock_dI.lockForWrite();
    for(int i=0;i<days;i++){
        dayInformation[i].updateTime = _obj.value("updateTime").toString();
        QJsonObject _obj2 = _array[i].toObject();
        dayInformation[i].fxDate = _obj2.value("fxdate").toString();
        dayInformation[i].sunrise = _obj2.value("sunrise").toString();
        dayInformation[i].sunset = _obj2.value("sunset").toString();
        dayInformation[i].moonrise = _obj2.value("moonrise").toString();
        dayInformation[i].moonset = _obj2.value("moonset").toString();
        dayInformation[i].moonPhase = _obj2.value("moonPhase").toString();
        dayInformation[i].moonPhaseIcon = _obj2.value("moonPhaseIcon").toString();
        dayInformation[i].tempMax = _obj2.value("tempMax").toString();
        dayInformation[i].tempMin = _obj2.value("tempMin").toString();
        dayInformation[i].iconDay = _obj2.value("iconDay").toString();
        dayInformation[i].textDay = _obj2.value("textDay").toString();
        dayInformation[i].iconNight = _obj2.value("iconNight").toString();
        dayInformation[i].textNight = _obj2.value("textNight").toString();
        dayInformation[i].wind360Day = _obj2.value("wind360Day").toString();
        dayInformation[i].windDirDay = _obj2.value("windDirDay").toString();
        dayInformation[i].windScaleDay = _obj2.value("windScaleDay").toString();
        dayInformation[i].windSpeedDay = _obj2.value("windSpeedDay").toString();
        dayInformation[i].wind360Night = _obj2.value("wind360Night").toString();
        dayInformation[i].windDirNight = _obj2.value("windDirNight").toString();
        dayInformation[i].windScaleNight = _obj2.value("windScaleNight").toString();
        dayInformation[i].windSpeedNight = _obj2.value("windSpeedNight").toString();
        dayInformation[i].humidity = _obj2.value("humidity").toString();
        dayInformation[i].precip = _obj2.value("precip").toString();
        dayInformation[i].pressure = _obj2.value("pressure").toString();
        dayInformation[i].vis = _obj2.value("vis").toString();
        dayInformation[i].cloud = _obj2.value("cloud").toString();
        dayInformation[i].uvIndex = _obj2.value("uvIndex").toString();
    }
    rwLock_dI.unlock();
}
void QweatherAPIService::slot_updateAPIcity(){
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.vvhan.com/api/ipInfo"));
    
    QNetworkReply *reply = manager.get(request);
    
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    
    if (reply->error()) {
        qDebug() << "Error occurred: " << reply->errorString();
    } else {
        QByteArray response_data = reply->readAll();
        qDebug() << "Response content:\n" << response_data;
        analyzeCityData(response_data);
    }
    reply->deleteLater();
}
void QweatherAPIService::slot_updateAPIlocationid(){
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://geoapi.qweather.com/v2/city/lookup?location=%1&key=63052cfc2b8744b083b861f55f762a38").arg(city)));
    
    QNetworkReply *reply = manager.get(request);
    
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    
    if (reply->error()) {
        qDebug() << "Error occurred: " << reply->errorString();
    } else {
        QByteArray response_data = reply->readAll();
        qDebug() << "Response content:\n" << response_data;
        analyzelocationID(response_data);
    }
    reply->deleteLater();
}
void QweatherAPIService::slot_updateAPIweather(){
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://devapi.qweather.com/v7/weather/3d?location=%1&key=63052cfc2b8744b083b861f55f762a38").arg(locationID)));
    
    QNetworkReply *reply = manager.get(request);
    
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    
    if (reply->error()) {
        qDebug() << "Error occurred: " << reply->errorString();
    } else {
        QByteArray response_data = reply->readAll();
        qDebug() << "Response content:\n" << response_data;
        analyzeWeatherData(response_data);
    }
    reply->deleteLater();
}
void QweatherAPIService::slot_updateAPIweathernow(){
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://devapi.qweather.com/v7/weather/now?location=%1&key=63052cfc2b8744b083b861f55f762a38").arg(locationID)));
    
    QNetworkReply *reply = manager.get(request);
    
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    
    if (reply->error()) {
        qDebug() << "Error occurred: " << reply->errorString();
    } else {
        QByteArray response_data = reply->readAll();
        qDebug() << "Response content:\n" << response_data;
        analyzeWeathernowData(response_data);
    }
    reply->deleteLater();
}
void QweatherAPIService::slot_updatedt(){
//    qDebug()<<"running slot_updatedt";
    rwLock_dt.lockForWrite();
    dt = QDateTime::currentDateTime();
    rwLock_dt.unlock();
//    emit WeatherAPI::signal_timechanged();
//    if(WeatherAPI::getTime()=="00:00") emit WeatherAPI::signal_datechanged();
    
}
void QweatherAPIService::analyzeCityData(QByteArray _data){
    QJsonDocument _doc = QJsonDocument::fromJson(_data);
    if (!_doc.isNull()) {
        QJsonObject jsonObj = _doc.object();
        
        QJsonObject infoObj = jsonObj.value("info").toObject();
        city = getCityEnglishName(infoObj.value("city").toString());
        
        qDebug() << "City: " << city;

    } else {
        qDebug() << "Failed to parse JSON.";
    }
}
void QweatherAPIService::analyzeWeathernowData(QByteArray _data){
    QJsonDocument _doc = QJsonDocument::fromJson(_data);
    if (!_doc.isNull()) {
        QJsonObject jsonObj = _doc.object();
        
        QJsonObject infoObj = jsonObj.value("now").toObject();
        temperaturenow = infoObj.value("temp").toString();
        
        qDebug() << "Temperaturenow: " << temperaturenow;

    } else {
        qDebug() << "Failed to parse JSON.";
    }
}
void QweatherAPIService::analyzelocationID(QByteArray _data){
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(_data, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse JSON:" << jsonError.errorString();
        return;
    }
    
    // 获取JSON对象
    QJsonObject jsonObject = doc.object();
    
    // 获取'location'数组
    QJsonArray locationArray = jsonObject.value("location").toArray();
    
    // 获取第一个元素的'id'
    if (!locationArray.isEmpty()) {
        QJsonObject firstLocation = locationArray.at(0).toObject();
        locationID = firstLocation.value("id").toString();
        qDebug() << "First location ID:" << locationID;
    } else {
        qDebug() << "Location array is empty.";
    }
}
QString QweatherAPIService::getCityEnglishName(const QString &chineseCityName){
    const QString jsonFilePath = ":/json/src/json/CNcitylists.json";

    // 加载并解析JSON文件
    QFile file(jsonFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Failed to open the JSON file.");
        return QString();
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning("Failed to parse JSON data.");
        return QString();
    }

    if (!jsonDoc.isObject()) {
        qWarning("The JSON document is not an object.");
        return QString();
    }

    QJsonObject jsonObject = jsonDoc.object();

    // 验证是否存在'rows'数组
    if (!jsonObject.contains("rows") || !jsonObject["rows"].isArray()) {
        qWarning("Invalid JSON format: missing 'rows' array.");
        return QString();
    }

    QJsonArray rowsArray = jsonObject["rows"].toArray();
    for (const QJsonValue &rowValue : rowsArray) {
        if (!rowValue.isObject()) {
            continue;
        }

        QJsonObject rowObject = rowValue.toObject();
        if (rowObject.contains("Field_2") && rowObject["Field_2"].toString() == chineseCityName) {
            if (rowObject.contains("Field_4")) {
                return rowObject["Field_4"].toString();
            }
        }
    }

    // 如果没有找到对应的城市，返回空字符串
    return QString();
}

/**********************************/

QWeather::QWeather(QObject *parent) : IWeatherinfo(parent)
{
    InitQWeatherAPIService();
}
void QWeather::InitQWeatherAPIService(){
    qWA = new QweatherAPIService(nullptr);
    QThread *serviceThread = new QThread();
    qWA->moveToThread(serviceThread);
    
    connect(serviceThread, &QThread::started, qWA, &QweatherAPIService::startService, Qt::QueuedConnection);
    connect(serviceThread, &QThread::finished, qWA, &QObject::deleteLater, Qt::QueuedConnection);
    connect(serviceThread, &QThread::finished, serviceThread, &QObject::deleteLater, Qt::QueuedConnection);
    
    serviceThread->start();
}
QString QWeather::getTodayIcon(){
    return QString(":/weathericons/src/weathericons/%1.svg").arg(dayInformation[Today].iconDay);
}
QString QWeather::getTomorrowIcon(){
    return QString(":/weathericons/src/weathericons/%1.svg").arg(dayInformation[Tomorrow].iconDay);
}
QString QWeather::getThirdayIcon(){
    return QString(":/weathericons/src/weathericons/%1.svg").arg(dayInformation[ThirdDay].iconDay);
}
QString QWeather::getNowTemp(){
    return QString("%1℃").arg(temperaturenow);
}
QString QWeather::getTodayMaxTemp(){
    return QString("%1℃").arg(temperaturenow);
    return dayInformation[Today].tempMax;
}
QString QWeather::getTodayMinTemp(){
    return QString("%1℃").arg(dayInformation[Today].tempMin);
}
QString QWeather::getTomorrowMaxTemp(){
    return QString("%1℃").arg(dayInformation[Tomorrow].tempMax);
}
QString QWeather::getTomorrowMinTemp(){
    return QString("%1℃").arg(dayInformation[Tomorrow].tempMin);
}
QString QWeather::getThirdayMaxTemp(){
    return QString("%1℃").arg(dayInformation[ThirdDay].tempMax);
}
QString QWeather::getThirdayMinTemp(){
    return QString("%1℃").arg(dayInformation[ThirdDay].tempMin);
}
