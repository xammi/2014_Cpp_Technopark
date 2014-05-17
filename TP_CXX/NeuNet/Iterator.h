#ifndef ITERATOR_H
#define ITERATOR_H

#include "Neuron.h"
#include "AbstractIterator.h"

namespace NeuNets {

class Iterator : public AbstractIterator
{
    friend class MultiLayerNet;
    friend class Factory::MultiLayerDestroyer;

public:

    void prevLayer();
    void nextLayer();

    Neuron &operator[](int i);
    const Neuron &operator[](int i) const;

    const Neuron &nextNeuron();
    const Neuron &prevNeuron();

    bool operator==(const Iterator &rhs) const;
    bool operator!=(const Iterator &rhs) const { return !(*this == rhs); }

    void apply(UnmodNeuronAct);
    void apply(NeuronAct);

    int count() const { return neuronLayer.size(); }


protected:
    void zeroFlags() {flagPseudoEnd = false; flagPseudoBegin = false;}

    bool flagPseudoEnd;
    bool flagPseudoBegin;

    Iterator(const NeuVec &);
    NeuVec neuronLayer;
    int ptrPos; //contains the position of pointer in vector

    void apply(UnsafeNeuronAct);
};
//-------------------------------------------------------------------------------------------------
struct  FailInitializedIter: public Exception {
    QString toString() { return "Failed to initialize the iterator"; }
};

struct  NoPrevLayer: public Exception {
    QString toString() { return "No previous layer"; }
};

struct  NoNextLayer: public Exception {
    QString toString() { return "No next layer"; }
};

struct  PosOutOfRange: public Exception {
    QString toString() { return "Internal cursor out of range"; }
};


}//namespace NeuNets
#endif // ITERATOR_H

