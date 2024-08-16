HEADERS += \
    $$PWD/wifipannel.h \
    $$PWD/wifipassworddialog.h \
    $$PWD/wifiwpa_package.h \
    $$PWD/wpa_ctrl.h

SOURCES += \
    $$PWD/wifipannel.cpp \
    $$PWD/wifipassworddialog.cpp \
    $$PWD/wifiwpa_package.cpp

DISTFILES += \
    $$PWD/libwpa_client.so

LIBS += -L$$PWD/ -lwpa_client
DEPENDPATH += $$PWD/

FORMS += \
    $$PWD/wifipannel.ui \
    $$PWD/wifipassworddialog.ui
