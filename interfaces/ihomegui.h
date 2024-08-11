#ifndef IHOMEGUI_H
#define IHOMEGUI_H

#include <QWidget>

class IHomeGUI : public QWidget
{
    Q_OBJECT
public:
    explicit IHomeGUI(QWidget *parent = nullptr):QWidget(parent){};
    virtual void showHomeForm() = 0;
    virtual void closeHomeForm() = 0;
    virtual void setNowTemp(QString _temp) = 0;
    virtual void setTodayMaxTemp(QString _temp) = 0;
    virtual void setTodayMinTemp(QString _temp) = 0;
    virtual void setTomorrowMaxTemp(QString _temp) = 0;
    virtual void setTomorrowMinTemp(QString _temp) = 0;
    virtual void setThirdayMaxTemp(QString _temp) = 0;
    virtual void setThirdayMinTemp(QString _temp) = 0;
    virtual void setTodayIcon(QString _path) = 0;
    virtual void setTomorrowIcon(QString _path) = 0;
    virtual void setThirdayIcon(QString _path) = 0;
    virtual void setNowTime(QString _time) = 0;
    virtual void setTodayDate(QString _date) = 0;
    virtual void setNowLocation(QString _location) = 0;
    virtual void setTodayWeek(QString _week) = 0;
    virtual void setTomorrowWeek(QString _week) = 0;
    virtual void setThirdayWeek(QString _week) = 0;
    
    
    
signals:
    
};

#endif // IHOMEGUI_H
