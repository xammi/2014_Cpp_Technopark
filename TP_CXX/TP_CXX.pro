#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T00:26:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TP_CXX
TEMPLATE = app


SOURCES +=  main.cpp\
            NetManagers/neunetui.cpp \
            NetManagers/netprocessor.cpp \
            NetManagers/imagestorage.cpp

HEADERS  += NetManagers/neunetui.h \
            NetManagers/netprocessor.h \
            NetManagers/imagestorage.h \
            includes.h

FORMS    +=   NetManagers/neunetui.ui
