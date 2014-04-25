#include "MultiLayerDestroyer.h"
#include <QFile>

const quint32 fileId  = 0xA1B1C1D1;


namespace Factory{



MultiLayerDestroyer::MultiLayerDestroyer() {
}

void MultiLayerDestroyer::destroy(NeuNets::MultiLayerNet *nNet) {
    if(!nNet)
        throw NetNotFound();

    NeuNets::Iterator from = nNet->getInLayer();
    NeuNets::Iterator to = nNet->getOutLayer();
/*
    1. Replace the usual iterator with our own;
         The problem: net doesn't know about it;and we cannot convert usual iterator to derived one.
         Solution: 1. Forget about iterator hierarchy and biuld templates on getIn/OutLayer()

     * 2. Forse iterator to delete neurons.
     * 3. Destroy the destroyer and use net destructor.
     * 4. Not use iterator altogether. Just relation of friendship with MultiLayerNet.
     * 5.
     */

    NeuNets::Neuron *prevNeuron;
    NeuNets::Neuron *curNeuron;
//    while(from != to){
//        curNeuron = from[0];
//        do{
//            prevNeuron = curNeuron;
//            if(!prevNeuron)
//                throw NeuronNotFound();
//            curNeuron = from.nextNeuron();

//            for(int i = 0; i < prevNeuron->getInSyn().count(); ++i){
//                delete prevNeuron->getInSyn()[i];
//            }
//            for(int i = 0; i < prevNeuron->getOutSyn().count(); ++i){
//                delete prevNeuron->getOutSyn()[i];
//            }
//            delete prevNeuron;

//        }
//        while(curNeuron);
//        from.nextLayer();
//    }
}



 /*Пока не дописываю этот кусок - неизвестно, что там с форматом файла
  *
  */


void MultiLayerDestroyer::writeFile(NeuNets::MultiLayerNet *nNet, const QString &filename) {
    if(!nNet)
        throw NetNotFound();

    NeuNets::Iterator firstIter = nNet->getInLayer();
    NeuNets::Iterator lastIter = nNet->getOutLayer();

    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
        throw FileNotFound();

    QTextStream stream(&file);

    stream << fileId;

//    while(firstIter != lastIter){
//        NeuNets::Neuron bufNeuron = firstIter.nextNeuron();



//        firstIter.nextLayer();
//    }

}

} // namespace Factory
