#include "NetManagers/NetProcessor.h"
#include "DataProcess/ImageProcessor.h"
#include <QApplication>
#include <iostream>

using namespace DataProcess;

int main(int argc, char *argv[]) {
    QImage testImg("C:/Qt/2014_Cpp_Technopark/TP_CXX/Default\ store/test.bmp"/*, QImage::Format_RGB32*/);
    ImageProcessor procObj;
    InputData inData;
    InputDataSet dataSet(1);

    procObj.prepareImg(inData, testImg);

    procObj.prepareImgSet(dataSet, testImg);
    return procObj.getSegm();

}

/*
 * Отстойное сохранение сети
 */
