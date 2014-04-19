#ifndef ABSTRNET_H
#define ABSTRNET_H

#include "../includes.h"
#include "Neuron.h"

namespace NeuNets {

typedef QVector<Neuron *> NeuVec;

class AbstractNet
{
public:
    virtual OutputData getResponse(const InputData &) = 0;

};
}//namespace NeuNets {
#endif // ABSTRNET_H
