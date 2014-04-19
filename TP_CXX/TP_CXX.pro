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
    DataProcess/ImageStorage.cpp \
    NetManagers/NetProcessor.cpp \
    NetManagers/NeuNetUI.cpp \
    NetManagers/Tester.cpp \
    NetTutors/BackPropTutor.cpp \
    NeuNet/neuron.cpp \
    NeuNet/iterator.cpp \
    NeuNet/MultiLayerNet.cpp \
    Factory/MultiLayerFactory.cpp \
    Factory/NnDestroyer.cpp \
    DataProcess/OutputData.cpp \
    DataProcess/InputData.cpp \
    NeuNet/Neuron.cpp \
    NeuNet/Iterator.cpp

HEADERS  += \
    Factory/BuildInfo.h \
    Factory/backpropnet.h \
    Factory/BuildInfo.h \
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
    NeuNet/iterator.h \
    NeuNet/abstriterator.h \
    NeuNet/MultiLayerNet.h \
    NetTutors/TutitionData.h \
    Factory/AbstractNetFactory.h \
    Factory/MultiLayerFactory.h \
    Factory/NnAbstractDestroyer.h \
    Factory/NnDestroyer.h \
    DataProcess/OutputData.h \
    DataProcess/InputData.h \
    PtrVector.h \
    NeuNet/Neuron.h \
    NeuNet/Iterator.h \
    NeuNet/AbstractNet.h \
    NeuNet/AbstractIterator.h

FORMS    +=   NetManagers/neunetui.ui
