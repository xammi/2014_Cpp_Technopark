#ifndef ABSTRNET_H
#define ABSTRNET_H

#include "../includes.h"
#include "Neuron.h"
#include "../DataProcess/AbstractProcessor.h"

namespace NeuNets {

typedef QVector<Neuron *> NeuVec;

typedef function< void (Neuron *) > UnsafeNeuronAct;
typedef function< void (Neuron &) > NeuronAct;
typedef function< void (const Neuron &) > UnmodNeuronAct;

class AbstractNet
{
public:
    virtual DataProcess::OutputData getResponse(const InputData &) = 0;

};
}//namespace NeuNets {
#endif // ABSTRNET_H
