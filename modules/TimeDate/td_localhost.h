#ifndef TD_LOCALHOST_H
#define TD_LOCALHOST_H

#include <QObject>
#include <QDateTime>

#include "itimedate.h"

#define TIMEFORMAT "HH:mm:ss"
#define DATEFORMAT "MM/dd/yyyy"

class TD_LocalHost : public ITimeDate
{
    Q_OBJECT
public:
    explicit TD_LocalHost(QObject *parent = nullptr);
    ~TD_LocalHost();
    QString getNowTime() override;
    QString getTodayDate() override;
    QString getTodayWeek() override;
    QString getTomorrowWeek() override;
    QString getThirdayWeek() override;
private:
    
    
signals:
    
};

#endif // TD_LOCALHOST_H
