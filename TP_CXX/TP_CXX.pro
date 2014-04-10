#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T00:26:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TP_CXX
TEMPLATE = app

SOURCES += main.cpp \
    Factory/nndestroyer.cpp \
    Factory/backpropnet.cpp \
    Factory/backpropfactory.cpp \
    DataProcess/ImageProcessor.cpp \
    DataProcess/ImageStorage.cpp \
    NetManagers/NetProcessor.cpp \
    NetManagers/NeuNetUI.cpp \
    NetManagers/Tester.cpp \
    NetTutors/BackPropTutor.cpp \
    NeuNet/neuron.cpp \
    NeuNet/neunet.cpp \
    NeuNet/iterator.cpp \
    NeuNet/abstrnet.cpp \
    NeuNet/abstriterator.cpp

HEADERS  += \
    Factory/nndestroyer.h \
    Factory/nnabstractdestroyer.h \
    Factory/BuildInfo.h \
    Factory/backpropnet.h \
    Factory/backpropfactory.h \
    Factory/abstractnetfactory.h \
    Factory/nndestroyer.h \
    Factory/nnabstractdestroyer.h \
    Factory/BuildInfo.h \
    Factory/backpropnet.h \
    Factory/backpropfactory.h \
    Factory/abstractnetfactory.h \
    Factory/abstractnet.h \
    includes.h \
    DataProcess/AbstractProcessor.h \
    DataProcess/AbstractStorage.h \
    DataProcess/ImageProcessor.h \
    DataProcess/ImageStorage.h \
    NetManagers/NetProcessor.h \
    NetManagers/NeuNetUI.h \
    NetManagers/Tester.h \
    NetTutors/BackPropTutor.h \
    NetTutors/AbstractTutor.h \
    NeuNet/neuron.h \
    NeuNet/neunet.h \
    NeuNet/iterator.h \
    NeuNet/abstrnet.h \
    NeuNet/abstriterator.h


FORMS    +=   NetManagers/neunetui.ui
