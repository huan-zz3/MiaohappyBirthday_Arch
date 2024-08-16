#ifndef MYGTEST_H
#define MYGTEST_H

#include <QObject>
#include <QApplication>
#include <gtest/gtest.h>

class myGTest : public QObject
{
    Q_OBJECT
public:
    explicit myGTest(QObject *parent = nullptr):QObject(parent){};
public slots:
    void startGTest(){
        ::testing::InitGoogleTest();
        int result = RUN_ALL_TESTS();
        // 可能需要在此处处理测试结果，比如根据result退出应用程序
        qApp->quit();
    }
signals:
    
};

#endif // MYGTEST_H
