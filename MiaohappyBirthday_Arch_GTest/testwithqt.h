#ifndef TESTWITHQT_H
#define TESTWITHQT_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>


#include <QString>
#include <QDebug>

#include "../modules/Location/l_hxhwebapi.h"


class TestwithQt : public testing::Test
{
protected:
    void SetUp() override{
        lh_ = new L_HxhWebAPI();
    }
    void TearDown() override{
        lh_->deleteLater();
    }
    L_HxhWebAPI *lh_;
};

#endif // TESTWITHQT_H
