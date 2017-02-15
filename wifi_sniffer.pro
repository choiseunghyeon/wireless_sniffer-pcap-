TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpcap
SOURCES += main.c \
    function.c

HEADERS += \
    packetinfo.h \
    wirelessframe.h \
    function.h

