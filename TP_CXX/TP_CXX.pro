#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T00:26:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TP_CXX
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp \
    DataProcess/ImageProcessor.cpp \
\
    NetManagers/NetProcessor.cpp \
    NetManagers/NeuNetUI.cpp \
    NetManagers/Tester.cpp \
\
    NetTutors/BackPropTutor.cpp \
\
    Factory/MultiLayerFactory.cpp \
    Factory/MultiLayerDestroyer.cpp \
\
    NeuNet/Neuron.cpp \
    NeuNet/Iterator.cpp \
    NeuNet/MultiLayerNet.cpp \
    NetFunction.cpp \
    Factory/BuildInfo.cpp \
    DataProcess/FileStorage.cpp \
    NetTutors/TuteModule.cpp

HEADERS  += \
    includes.h \
\
    DataProcess/AbstractProcessor.h \
    DataProcess/ImageProcessor.h \
\
    NetManagers/NetProcessor.h \
    NetManagers/NeuNetUI.h \
    NetManagers/Tester.h \
\
    NetTutors/BackPropTutor.h \
    NetTutors/AbstractTutor.h \
\
    Factory/MultiLayerFactory.h \
    Factory/MultiLayerDestroyer.h \
    Factory/BuildInfo.h \
\
    NeuNet/Neuron.h \
    NeuNet/Iterator.h \
    NeuNet/MultiLayerNet.h \
    NeuNet/AbstractIterator.h \
    NeuNet/AbstractNet.h \
    NetFunction.h \
    Factory/AbstractDestroyer.h \
    Factory/AbstractFactory.h \
    NetTutors/TuteData.h \
    DataProcess/FileStorage.h \
    NetTutors/TuteModule.h


FORMS    +=   NetManagers/neunetui.ui \
    NetManagers/createNet.ui \
    NetManagers/addLimits.ui
