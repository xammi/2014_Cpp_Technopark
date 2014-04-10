#ifndef NEURON_H
#define NEURON_H

#include "../includes.h"

namespace NeuNets{
enum neuronPos {input, hidden, output};

struct Synaps;

class Neuron {
public:
    Neuron();
    double summup();
    int changeOutSyn(double *neuWeights);

private:
    neuronPos layer;
    QVector<Synaps *> inSyn;
    QVector<Synaps *> outSyn;
};

struct Synaps {
    double weight;
    Neuron *to;
    Neuron *from;
};
}//namespace NeuNets
#endif // NEURON_H
