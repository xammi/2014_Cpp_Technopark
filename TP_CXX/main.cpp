#include "NetManagers/NetProcessor.h"
#include <QApplication>
#include "Factory/MultiLayerFactory.h"
#include "Factory/BuildInfo.h"
#include "Factory/MultiLayerDestroyer.h"

using NetManagers::NetProcessor;
using Factory::MultiLayerFactory;
using NeuNets::MultiLayerNet;


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Factory::MultiLayerFactory fac;
    Factory::BuildInfo info;
    NeuNets::MultiLayerNet *nNet;
    Factory::MultiLayerDestroyer destr;
    info.layersCount = 3;
    info.funcName = "Sigmoid";
    info.neuronsPerLayer.append(2);
    info.neuronsPerLayer.append(2);
    info.neuronsPerLayer.append(2);

    nNet = fac.createFromInfo(info);
    destr.destroy(nNet);
//    fac.createFromFile("text.txt");
    NetProcessor::get_self();

    return a.exec();
}
