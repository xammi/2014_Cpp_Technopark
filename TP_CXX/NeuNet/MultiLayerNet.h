#ifndef NEUNET_H
#define NEUNET_H


#include "AbstractNet.h"
#include "../DataProcess/AbstractProcessor.h"
#include "Iterator.h"
#include "../DataProcess/AbstractProcessor.h"


namespace NeuNets {


using DataProcess::InputData;
using DataProcess::OutputData;


class MultiLayerNet : public AbstractNet {

public:
    MultiLayerNet();

    MultiLayerNet(const Func &, const NeuVec &, const NeuVec &, const uint);
    ~MultiLayerNet();

    OutputData getResponse(const InputData &imgs) const;


    Iterator getInLayer() const;
    Iterator getOutLayer() const;
    Iterator getAfterOut() const;
    Iterator getBeforeIn() const;

    uint count() const { return layersCnt; }
    QString topology() const;

private:
    NeuVec outNeurons;
    NeuVec inNeurons;
    uint inLayerNum, outLayerNum;
    uint layersCnt;
    Func sigmoid;
};


struct  NoImageForResp: public Exception {
    QString toString() { return "Fail to get image for response"; }
};

} //namespace NeuNets
#endif // NEUNET_H
