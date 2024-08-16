#include <QApplication>
#include "mygtest.h"
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    myGTest *mygtest = new myGTest();
    
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, mygtest, &myGTest::startGTest);
    QObject::connect(&timer, &QTimer::timeout, &timer, &QTimer::stop);
    timer.start(500);
    
//    ::testing::InitGoogleTest(&argc, argv);
    
    
    return app.exec();
}

