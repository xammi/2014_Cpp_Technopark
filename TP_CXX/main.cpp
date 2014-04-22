#include "NetManagers/NetProcessor.h"
#include <QApplication>
#include "Factory/MultiLayerFactory.h"

using NetManagers::NetProcessor;
using Factory::MultiLayerFactory;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    Factory::MultiLayerFactory Fac;

    NetProcessor::get_self();

    return a.exec();
}
