#ifndef UI_HOME_H
#define UI_HOME_H

#include <QWidget>
#include <QDebug>
#include <QTimer>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QFontDatabase>
#include <QGraphicsRectItem>
#include <QRadialGradient>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QResource>
#include <QCursor>

#include "ihomegui.h"
#include "grapview_centre.h"
#include "grapview_home.h"

#define weektextXoffset -20
#define temptextXoffset 10

namespace Ui {
class UI_Home;
}

class UI_Home : public IHomeGUI
{
    Q_OBJECT
    
public:
    explicit UI_Home(QWidget *parent = nullptr);
    ~UI_Home();
    
    void showHomeForm()  override;
    void closeHomeForm()  override;
    void setNowTemp(QString _temp)  override;
    void setTodayMaxTemp(QString _temp)  override;
    void setTodayMinTemp(QString _temp)  override;
    void setTomorrowMaxTemp(QString _temp)  override;
    void setTomorrowMinTemp(QString _temp)  override;
    void setThirdayMaxTemp(QString _temp)  override;
    void setThirdayMinTemp(QString _temp)  override;
    void setTodayIcon(QString _path)  override;
    void setTomorrowIcon(QString _path)  override;
    void setThirdayIcon(QString _path)  override;
    void setNowTime(QString _time)  override;
    void setTodayDate(QString _date)  override;
    void setNowLocation(QString _location)  override;
    void setTodayWeek(QString _week)  override;
    void setTomorrowWeek(QString _week) override;
    void setThirdayWeek(QString _week) override;
    
public slots:
//    void slot_updateInSecond();
    
private:
    Ui::UI_Home *ui;
    QTimer *timeSecond;
    
    QGraphicsScene *mainScene;
    GrapView_home *mainView;
    QGraphicsRectItem *rect;
    QGraphicsScene *subScene;
    GrapView_centre *subView;
    QGraphicsProxyWidget *proxyWidget;
    
    QGraphicsTextItem *time, *date, *location, *temperaturenow, *week[3], *temperaturescale[3][2];
    QGraphicsRectItem *maskrect;
    QGraphicsPixmapItem *pixmenu, *bless;
    QGraphicsSvgItem *weathericon[3];
    QString timeString, dateString, locationString, temperaturenowString, weekString[3], temperaturescaleString[3][2];
    QSvgRenderer *weathericonrenderer[3];
    
    
    void initView();
    QString loadFont(QString);
    void initsubScene();
    void initconnect();
    
signals:
//    void signal_MenuPress();
};

#endif // UI_HOME_H
