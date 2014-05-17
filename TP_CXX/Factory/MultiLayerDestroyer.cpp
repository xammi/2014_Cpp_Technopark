#include "MultiLayerDestroyer.h"
#include <QFile>

//const quint32 fileId  = 0xA1B1C1D1;
const qint32 fileId = 10;

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
    NeuNets::Iterator buf = nNet->getInLayer();
    NeuNets::Iterator to = nNet->getAfterOut();

    // Даже сравнение не проходит. Проблема в том, что при вызове nextLayer
    // почему-то меняются нейроны местами. В результате флаги сохраняются
    // а значения синапсов другие

    for ( ; from != to; from.nextLayer()) {
        buf.nextLayer();
        from.apply(deleteNeurons);
        from = buf;
    }
}

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
    NeuNets::Iterator to = nNet->getAfterOut();

    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
        throw FileNotFound();

    QTextStream stream(&file);

    stream << fileId;
    stream << nNet->count();

    stream << from.count();
    from.nextLayer();

    SynapseAct sAct = [ &stream ] (Synaps &synapse) {
        stream << synapse.weight;
    };
    NeuronAct nAct = [ &sAct ] (Neuron &neuron) {
        neuron.apply(sAct, IN_OUT);
    };

    for ( ; from != to; from.nextLayer()) {
        stream << from.count();
        from.apply(nAct);
    }
}

} // namespace Factory
