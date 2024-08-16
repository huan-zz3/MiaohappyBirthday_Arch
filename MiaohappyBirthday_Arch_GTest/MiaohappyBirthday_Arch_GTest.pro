include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt
CONFIG += qt network
QT += core gui network svg widgets

SOURCES += \
        main.cpp         tst_casename.cpp \
        testwifi.cpp \
        testwithqt.cpp

HEADERS += \
    mygtest.h \
    testwifi.h \
    testwithqt.h
    
RESOURCES += ../src.qrc

include(../modules/modules.pri)
include(../interfaces/interfaces.pri)
INCLUDEPATH += $$PWD/../interfaces

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
