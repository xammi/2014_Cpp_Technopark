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


//--------------------------------------
struct Layer {
    uint neuroCount;

    // last layer doesn't have Synapses;
    // Seems like one needless variable;
    bool isLast;
    QVector <NeuNets::Neuron *> neuron;
    QVector <NeuNets::Synaps *> synaps;
};

Layer *prevLayer;
Layer *curLayer;


//--------------------------------------


// Concrete Factory
class BackPropFactory: public AbstractNetFactory
{
private:
    buildInfo nnInfo;
    NeuNets::MultiLayerNet *bpNewNet;

public:
    virtual NeuNets::AbstrNet *createNet(QString filename);
    virtual void parseFile(QString filename);
    void allocMemory() ;
    void assembly(Layer *prevLayer, Layer *curLayer);
};

} // namespace Factory
#endif // BACKPROPNETFACTORY_H
