#ifndef TESTWALLPAPER_H
#define TESTWALLPAPER_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>


#include <QString>
#include <QDebug>

#include "../modules/WallpaperGUI/ui_wallpaper.h"

class TestWallpaper : public testing::Test
{
protected:
    void SetUp() override{
        ui = new UI_Wallpaper();
    }
    void TearDown() override{
        ui->deleteLater();
    }
    UI_Wallpaper *ui;
};

#endif // TESTWALLPAPER_H
