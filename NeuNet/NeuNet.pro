#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T13:32:14
#
#-------------------------------------------------

QT       -= gui

TARGET = NeuNet
TEMPLATE = lib

DEFINES += NEUNET_LIBRARY

SOURCES += neunet.cpp

HEADERS += neunet.h\
        NeuNet_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0BAD619
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = NeuNet.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
