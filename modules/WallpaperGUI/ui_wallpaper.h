#ifndef UI_WALLPAPER_H
#define UI_WALLPAPER_H

#include "IWallpaper.h"
#include <QPixmap>
#include <QPalette>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QStringList>
#include <QTimer>

#define DIRECTORYPATH "/opt/MiaohappyBirthday_Arch/bin/wallpaper/"

namespace Ui {
class UI_Wallpaper;
}

class UI_Wallpaper : public IWallpaper
{
    Q_OBJECT
    
public:
    explicit UI_Wallpaper(QWidget *parent = nullptr);
    ~UI_Wallpaper();
    
    void showWallpaperForm() override;
    void closeWallpaperForm() override;
    void nextPicture() override;
    void lastPicture() override;
    void setIntervalTime(int msec) override;
    
private:
    Ui::UI_Wallpaper *ui;
    QStringList filePaths;
    int currentImage = 0;
    QTimer *switchtimer;
    
    void searchforWallpaper();
    void applyNewWallpaper(QString&);
};

#endif // UI_WALLPAPER_H
