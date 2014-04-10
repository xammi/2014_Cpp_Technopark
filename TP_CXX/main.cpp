#include "NetManagers/NetProcessor.h"
#include <QApplication>

using NetManagers::NetProcessor;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    NetProcessor::get_self();

    return a.exec();
}
