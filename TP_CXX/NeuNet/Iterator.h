#ifndef ITERATOR_H
#define ITERATOR_H

#include "Neuron.h"
#include "AbstractIterator.h"

namespace NeuNets {

class Iterator : public AbstractIterator
{
    friend class MultiLayerNet;
public:

    void prevLayer();//Set neuron vector in previous layer
    void nextLayer();//Set neuron vector in next layer
    const Neuron &operator[](int i); //Return pointer to i neuron in current layer
    const Neuron &nextNeuron(); // increase ptrPos if possible and return pointer to Neuron at ptrPos
    const Neuron &prevNeuron(); // decrease ptrPos if possible and return pointer to Neuron at ptrPos

private:
    Iterator(const NeuVec &);
    NeuVec neuronLayer;
    int ptrPos; //contains the position of pointer in vector

    bool isCorrect();
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


}//namespace NeuNets
#endif // ITERATOR_H


