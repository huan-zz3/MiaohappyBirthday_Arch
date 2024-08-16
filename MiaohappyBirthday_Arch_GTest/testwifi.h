#ifndef TESTWIFI_H
#define TESTWIFI_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDebug>

#include "../modules/WIFIGUI/wifiwpa_package.h"
#include "../modules/WIFIGUI/wifipannel.h"

class TestWIFI: public testing::Test
{
protected:
    void SetUp() override{
        wpa = new WIFIwpa_package();
        wpan = new WIFIPannel();
    }
    void TearDown() override{
        wpa->deleteLater();
        wpan->deleteLater();
    }
    WIFIwpa_package *wpa;
    WIFIPannel *wpan;
};

#endif // TESTWIFI_H
