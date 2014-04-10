#ifndef BACKPROPNETFACTORY_H
#define BACKPROPNETFACTORY_H

#include "abstractnetfactory.h"
#include "../NeuNet/MultiLayerNet.h"
#include "BuildInfo.h"

namespace Factory{

using NeuNets::Neuron;
using NeuNets::Synaps;
using NeuNets::MultiLayerNet;

struct Layer {
    uint neuroCount;

    // last layer doesn't have Synapses;
    bool is_last;
    QVector <Neuron *> neuron;
    QVector <Synaps *> synaps;
};

typedef QVector <Layer *> GlobalNet;

//--------------------------------------


// Concrete Factory
class BackPropFactory: public AbstractNetFactory
{
private:
    GlobalNet bpLayers;
    buildInfo nnInfo;
    MultiLayerNet *bpNewNet;

public:
    //virtual AbstractNet *createNet(FILE *file);
    //virtual void parseFile(FILE *file);
    void allocMemory() ;

    // подключение нейронов. С простановкой весов
    void assembly();
};
} // namespace Factory
#endif // BACKPROPNETFACTORY_H
