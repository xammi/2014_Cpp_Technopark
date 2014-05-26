#include "MultiLayerDestroyer.h"
#include <QFile>

//const quint32 fileId  = 0xA1B1C1D1;
const qint32 fileId = 10;

namespace Factory{

MultiLayerDestroyer::MultiLayerDestroyer() {
    deleteSynapses = [] (Synapse * synaps) {
        if (synaps)
            delete synaps;
    };

    deleteNeurons = [ this ] (Neuron * neuron) {
        if (neuron) {
            neuron->apply(deleteSynapses, IN);
            delete neuron;
        }
    };
}

void MultiLayerDestroyer::destroy(NeuNets::AbstractNet *aNet) {
    MultiLayerNet *nNet;
    try {
        nNet = dynamic_cast<MultiLayerNet *>(aNet);
    } catch (std::bad_cast) {
        throw WrongKindOfNet();
    }

    if(!nNet)
        throw NetNotFound();

    Iterator from = nNet->getInLayer(),
             buf = nNet->getInLayer(),
             to = nNet->getAfterOut();

    for ( ; from != to; from.nextLayer()) {
        buf.nextLayer();
        from.apply(deleteNeurons);
        from = buf;
    }
}


// TODO
void MultiLayerDestroyer::writeNetToFile(AbstractNet *aNet, const QString &filename) {
    MultiLayerNet *nNet;
    try {
        nNet = dynamic_cast<MultiLayerNet *>(aNet);
    } catch (std::bad_cast) {
        throw WrongKindOfNet();
    }

    if(!nNet)
        throw NetNotFound();

    Iterator from = nNet->getInLayer(),
             to = nNet->getAfterOut();

    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
        throw FileNotFound();

    QTextStream stream(&file);

    // FILEID?
    //
    // Program crashes when net is saved, then removed. Sometimes

    //
    //
    stream << fileId << endl;
    stream << nNet->getFunc().name() << endl;
    stream << nNet->getRecArea() << endl;
    stream << nNet->count() << endl;

    stream << from.count() << endl;
    from.nextLayer();

    SynapseAct sAct = [ &stream ] (Synapse &synapse) {
        stream << synapse.weight << endl;
    };
    NeuronAct nAct = [ &sAct ] (Neuron &neuron) {
        neuron.apply(sAct, IN);
    };

    for ( ; from != to; from.nextLayer()) {
        stream << from.count() << endl;
        from.apply(nAct);
    }
}

} // namespace Factory
