#include "MultiLayerDestroyer.h"
#include <QFile>

const quint32 fileId  = 0xA1B1C1D1;


namespace Factory{



MultiLayerDestroyer::MultiLayerDestroyer() {
    deleteSynapses = [] (NeuNets::Synaps * synaps)->void {
        if (synaps)
            delete synaps;
    };

    deleteNeurons = [ this ] (NeuNets::Neuron * neuron)->void {
        if (neuron) {
            neuron->apply(deleteSynapses, NeuNets::IN_OUT);
            delete neuron;
        }
    };
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
    for ( ; from != to; from.nextLayer()) {
        from.apply(deleteNeurons);
    }
}



 /*
  *Беда такая - куда писать кол-во слоев? Если вначале - то неудобно читать.
  *Если в конце - то неудобно писать.
  *И удаление вываливается просто так. Надо подключать веса
  *
  */


void MultiLayerDestroyer::writeFile(NeuNets::MultiLayerNet *nNet, const QString &filename) {
    if(!nNet)
        throw NetNotFound();

    NeuNets::Iterator from = nNet->getInLayer();
    NeuNets::Iterator to = nNet->getOutLayer();

    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
        throw FileNotFound();

    QTextStream stream(&file);

    stream << fileId;

    for ( ; from != to; from.nextLayer()) {
        from.apply(deleteNeurons);
    }

//    while(firstIter != lastIter){
//        NeuNets::Neuron bufNeuron = firstIter.nextNeuron();



//        firstIter.nextLayer();
//    }

}

} // namespace Factory
