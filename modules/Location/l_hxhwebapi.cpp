#include "l_hxhwebapi.h"

L_HxhWebAPI::L_HxhWebAPI(QObject *parent) : ILocation(parent)
{
    
}
QString L_HxhWebAPI::getNowLocation(){
    const QByteArray APIcitydata = getAPICity();
    const QString Englishcityname = analyzeCityData(APIcitydata);
    const QString Chinesecityname = getCityEnglishName(Englishcityname);
    return Chinesecityname;
}
QByteArray L_HxhWebAPI::getAPICity(){
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.vvhan.com/api/ipInfo"));
    
    QNetworkReply *reply = manager.get(request);
    
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    
    if (reply->error()) {
        qDebug() << "Error occurred: " << reply->errorString();
        reply->deleteLater();
        return "erro";
    } else {
        QByteArray response_data = reply->readAll();
        qDebug() << "Response content:\n" << response_data;
        reply->deleteLater();
        return response_data;
    }
}
QString L_HxhWebAPI::analyzeCityData(const QByteArray &_data){
    QJsonDocument _doc = QJsonDocument::fromJson(_data);
    if (!_doc.isNull()) {
        QJsonObject jsonObj = _doc.object();
        
        QJsonObject infoObj = jsonObj.value("info").toObject();
        return infoObj.value("city").toString();

    } else {
        qDebug() << "Failed to parse JSON.";
        return "erro";
    }
}
QString L_HxhWebAPI::getCityEnglishName(const QString &_ChineseCityName){
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
        if (rowObject.contains("Field_2") && rowObject["Field_2"].toString() == _ChineseCityName) {
            if (rowObject.contains("Field_4")) {
                return rowObject["Field_4"].toString();
            }
        }
    }

    // 如果没有找到对应的城市，返回空字符串
    return QString();
}
