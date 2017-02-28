TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += /home/choi/projects/wireless_sniffer-pcap-/jsmn
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += libmongoc-1.0
}
LIBS += -lpcap

SOURCES += main.c \
    function.c \
    db.c \
    json_parse.c \
    jsmn/jsmn.c

HEADERS += \
    packetinfo.h \
    wirelessframe.h \
    function.h \
    jsmn/jsmn.h

