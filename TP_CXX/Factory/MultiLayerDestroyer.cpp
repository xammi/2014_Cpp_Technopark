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
            neuron->apply(deleteSynapses, NeuNets::IN);
            delete neuron;
        }
    };
}

void MultiLayerDestroyer::destroy(NeuNets::AbstractNet *aNet) {
    NeuNets::MultiLayerNet *nNet;
    try {
        nNet = dynamic_cast<NeuNets::MultiLayerNet *>(aNet);
    } catch (std::bad_cast) {
        throw WrongKindOfNet();
    }

    if(!nNet)
        throw NetNotFound();

    NeuNets::Iterator from = nNet->getInLayer();
    NeuNets::Iterator to = nNet->getAfterOut();

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


void MultiLayerDestroyer::writeNetToFile(NeuNets::AbstractNet *aNet, const QString &filename) {
    NeuNets::MultiLayerNet *nNet;
    try {
        nNet = dynamic_cast<NeuNets::MultiLayerNet *>(aNet);
    } catch (std::bad_cast) {
        throw WrongKindOfNet();
    }

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

}

} // namespace Factory
