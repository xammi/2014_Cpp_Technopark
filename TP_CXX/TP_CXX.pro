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
    DataProcess/ImageProcessor.cpp \
    DataProcess/ImageStorage.cpp \
    NetManagers/NetProcessor.cpp \
    NetManagers/NeuNetUI.cpp \
    NetManagers/Tester.cpp \
    NetTutors/BackPropTutor.cpp

HEADERS  += \
            includes.h \
    DataProcess/AbstractProcessor.h \
    DataProcess/AbstractStorage.h \
    DataProcess/ImageProcessor.h \
    DataProcess/ImageStorage.h \
    NetManagers/NetProcessor.h \
    NetManagers/NeuNetUI.h \
    NetManagers/Tester.h \
    NetTutors/BackPropTutor.h \
    NetTutors/AbstractTutor.h

FORMS    +=   NetManagers/neunetui.ui
