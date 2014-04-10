#ifndef NEUNET_H
#define NEUNET_H
#include <stdio.h>


namespace Factory{

// TO BE DELETED
class Neuron {};
class Synaps {};

// Abstract Product
class AbstractNet
{
public:
    virtual void printName() = 0;
    virtual ~AbstractNet() {}
};

} // namespace Factory
#endif // NEUNET_H
