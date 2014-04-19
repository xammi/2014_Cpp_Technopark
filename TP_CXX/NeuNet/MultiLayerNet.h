#ifndef NEUNET_H
#define NEUNET_H

#include "Neuron.h"
#include "AbstractNet.h"
#include "Iterator.h"

namespace NeuNets {

class MultiLayerNet : public AbstractNet {

public:
    MultiLayerNet();
    MultiLayerNet(func sigmoid, const NeuVec &inNeu, const NeuVec &outNeu);
    ~MultiLayerNet();

    OutputData getResponse(const InputData &imgs);

    Iterator getInLayer() const;
    Iterator getOutLayer() const;

private:
    NeuVec outNeurons;
    NeuVec inNeurons;
    uint inLayerNum, outLayerNum;
    func sigmoid;
};

} //namespace NeuNets
#endif // NEUNET_H
