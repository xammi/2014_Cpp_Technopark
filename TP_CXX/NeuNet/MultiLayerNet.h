#ifndef NEUNET_H
#define NEUNET_H

#include "Neuron.h"
#include "AbstractNet.h"
#include "../DataProcess/AbstractProcessor.h"
#include "Iterator.h"

namespace NeuNets {

using DataProcess::OutputData;
using DataProcess::InputData;

class MultiLayerNet : public AbstractNet {

public:
    MultiLayerNet();
    MultiLayerNet(const Func &, const NeuVec &, const NeuVec &, const uint);
    ~MultiLayerNet();

    OutputData getResponse(const InputData &imgs);

    Iterator getInLayer() const;
    Iterator getOutLayer() const;

    uint count() const { return layersCnt; }
    QString topology() const;

private:
    NeuVec outNeurons;
    NeuVec inNeurons;
    uint inLayerNum, outLayerNum;
    uint layersCnt;
    Func sigmoid;
};

} //namespace NeuNets
#endif // NEUNET_H
