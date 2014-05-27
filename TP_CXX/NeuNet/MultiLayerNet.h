#ifndef NEUNET_H
#define NEUNET_H

#include "AbstractNet.h"
#include "../DataProcess/AbstractProcessor.h"

namespace NeuNets {
//-------------------------------------------------------

struct  NoImageForResp: public Exception {
    QString toString() { return "Fail to get image for response"; }
};

struct  RecAreaOutLayerSizeMismatch: public Exception {
    QString toString() { return "Recognition area doesn't suit this neuron net. Please, create a new NN"; }
};
//-------------------------------------------------------


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

    int getInSize() { return (int)inNeurons.size(); }
    int getOutSize() { return (int)outNeurons.size(); }

    void setRecArea(const QString &value) {
        if (value.length() == getOutSize()) { recArea = value; }
        else throw RecAreaOutLayerSizeMismatch();
    }
    uint count() const { return layersCnt; }
    QString topology() const;
    const Func &getFunc() { return activationFunc; }
    void clear();

private:
    NeuVec inNeurons;
    NeuVec outNeurons;
    Func activationFunc;
    uint inLayerNum, outLayerNum;
    uint layersCnt;
};



} //namespace NeuNets
#endif // NEUNET_H
