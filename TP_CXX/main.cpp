#include "NetManagers/NetProcessor.h"
#include <QApplication>
#include <iostream>

using NetManagers::NetProcessor;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    try {
        NetProcessor::get_self();
    } catch (std::bad_alloc & exc) {
        std::cerr << "Problems with set of configuration\n" << exc.what();
    } catch (Exception & exc) {

        std::cerr << "Problems with adjustment of configuration\n" << exc.toString().toStdString();
    }

    return a.exec();
}

/*
 * Отстойное сохранение сети
 */
