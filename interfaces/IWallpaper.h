#ifndef IWALLPAPER_H
#define IWALLPAPER_H

#include <QObject>
#include <QWidget>

class IWallpaper : public QWidget
{
    Q_OBJECT
public:
    explicit IWallpaper(QWidget *parent = nullptr):QWidget(parent){};
    
    virtual void showWallpaperForm() = 0;
    virtual void closeWallpaperForm() = 0;
    virtual void nextPicture() = 0;
    virtual void lastPicture() = 0;
    virtual void setIntervalTime(int msec) = 0;
    
signals:
    
};

#endif // IWALLPAPER_H
