#ifndef NEUNET_H
#define NEUNET_H

#include "Neuron.h"
#include "AbstractNet.h"
#include "Iterator.h"
#include "../DataProcess/AbstractProcessor.h"

namespace NeuNets {

class MultiLayerNet : public AbstractNet {

public:
    MultiLayerNet();

    MultiLayerNet (const Func &sigma,
                   const NeuVec &inNeuVec,
                   const NeuVec &outNeuVec,
                   const uint _layersCnt
                   );
    ~MultiLayerNet();

    DataProcess::OutputData getResponse(const InputData &imgs);

    Iterator getInLayer() const;
    Iterator getOutLayer() const;

    uint count() const { return layersCnt; }

private:
    NeuVec outNeurons;
    NeuVec inNeurons;
    uint inLayerNum, outLayerNum;
    uint layersCnt;
    Func sigmoid;
};

} //namespace NeuNets
#endif // NEUNET_H
