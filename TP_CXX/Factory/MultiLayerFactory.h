#ifndef BACKPROPNETFACTORY_H
#define BACKPROPNETFACTORY_H

#include "AbstractNetFactory.h"
#include "../NeuNet/MultiLayerNet.h"
#include "BuildInfo.h"

namespace Factory{

using NeuNets::Neuron;
using NeuNets::Synaps;
using NeuNets::MultiLayerNet;
using NeuNets::AbstrNet;


//-------------------------------------
//--------------------------------------


// Concrete Factory
class MultiLayerFactory: public AbstractNetFactory
{
    struct Layer {
        uint neuroCount;

        // last layer doesn't have Synapses;
        // Seems like one needless variable;
        bool isLast;
        QVector <NeuNets::Neuron *> neuron;
        QVector <NeuNets::Synaps *> synaps;
    };

private:
    BuildInfo nnInfo;
    NeuNets::MultiLayerNet *bpNewNet;

    void parseFile(const QString &filename);
    void allocMemory() ;
    void assembly(Layer &prevLayer, Layer &curLayer);

public:
    virtual NeuNets::AbstrNet *createNet(const QString &filename);

};

} // namespace Factory
#endif // BACKPROPNETFACTORY_H
