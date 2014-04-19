#ifndef ITERATOR_H
#define ITERATOR_H



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
    Iterator(const Iterator&);
    Iterator operator = (const Iterator&);
    NeuVec neuronLayer;
    int ptrPos; //contains the position of pointer in vector

    bool isCorrect();
};
}//namespace NeuNets
#endif // ITERATOR_H


