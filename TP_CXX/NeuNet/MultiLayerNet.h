#ifndef NEUNET_H
#define NEUNET_H


#include "AbstractNet.h"
#include "Iterator.h"
#include "/../DataProcess/InputData.h"
#include "/../DataProcess/OutputData.h"

namespace NeuNets {

using DataProcess::InputData;
using DataProcess::OutputData;

class MultiLayerNet : public AbstractNet {

public:
    MultiLayerNet();
    MultiLayerNet(func sigmoid, const NeuVec &inNeu, const NeuVec &outNeu);
    ~MultiLayerNet();

    OutputData getResponse(const InputData &imgs) const;

    Iterator getInLayer() const;
    Iterator getOutLayer() const;

private:
    NeuVec outNeurons;
    NeuVec inNeurons;
    uint inLayerNum, outLayerNum;
    func sigmoid;
};
//================================================================
struct  NoImage: public Exception {
    QString toString() { return "Fail to get image for response"; }
};

} //namespace NeuNets
#endif // NEUNET_H
