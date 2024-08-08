HEADERS += \
    $$PWD/gpiod.h \
    $$PWD/he_ld2410b.h \

SOURCES += \
    $$PWD/he_ld2410b.cpp

LIBS += -L$$PWD/ -lgpiod
DEPENDPATH += $$PWD/

DISTFILES += \
    $$PWD/libgpiod.so
