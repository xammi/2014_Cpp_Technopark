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

    void prevLayer();//Set neuron vector in previous layer
    void nextLayer();//Set neuron vector in next layer
    const Neuron &operator[](int i); //Return pointer to i neuron in current layer

    const Neuron &nextNeuron(); // increase ptrPos if possible and return pointer to Neuron at ptrPos
    const Neuron &prevNeuron(); // decrease ptrPos if possible and return pointer to Neuron at ptrPos

    bool operator==(const Iterator &rhs) const { return (neuronLayer == rhs.neuronLayer); }
    bool operator!=(const Iterator &rhs) const { return (neuronLayer != rhs.neuronLayer); }

    void apply(UnmodNeuronAct);
    void apply(NeuronAct);

protected:
    Iterator(const NeuVec &);

    NeuVec neuronLayer;
    int ptrPos; //contains the position of pointer in vector

    void apply(UnsafeNeuronAct);
    bool isCorrect();
};
}//namespace NeuNets
#endif // ITERATOR_H

