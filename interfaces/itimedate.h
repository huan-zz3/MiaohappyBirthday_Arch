#ifndef ITIMEDATE_H
#define ITIMEDATE_H

#include <QObject>
#include <QString>

class ITimeDate : public QObject
{
    Q_OBJECT
public:
    explicit ITimeDate(QObject *parent = nullptr):QObject(parent){};
    virtual QString getNowTime() = 0;
    virtual QString getTodayDate() = 0;
    virtual QString getTodayWeek() = 0;
    virtual QString getTomorrowWeek() = 0;
    virtual QString getThirdayWeek() = 0;
    
    
signals:
    
};

#endif // ITIMEDATE_H
