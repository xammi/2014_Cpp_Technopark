#include "MultiLayerDestroyer.h"
#include <QFile>

namespace Factory{

NNDestroyer::NNDestroyer() {
}

void NNDestroyer::destroy(NeuNets::MultiLayerNet *nNet) {
    if(!nNet)
        throw NetNotFound();

    // Все методы работы с НС возвращабт только константные указатели на нейроны
    NeuNets::Iterator firstIter = nNet->getInLayer();
    NeuNets::Iterator lastIter = nNet->getOutLayer();
    while(firstIter != lastIter){



        firstIter.nextLayer();
    }
}

void NNDestroyer::writeFile(NeuNets::MultiLayerNet *nNet, const QString &filename) {
    if(!nNet)
        throw NetNotFound();

    NeuNets::Iterator firstIter = nNet->getInLayer();
    NeuNets::Iterator lastIter = nNet->getOutLayer();

    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
        throw FileNotFound();

    QTextStream stream(&file);
    quint32 magicNumber = 0xA1B1C1D1;
    stream << magicNumber;

    while(firstIter != lastIter){



        firstIter.nextLayer();
    }

}

} // namespace Factory
