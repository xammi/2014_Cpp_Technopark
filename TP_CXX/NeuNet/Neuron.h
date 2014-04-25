#ifndef NEURON_H
#define NEURON_H

#include "../includes.h"
#include "../DataProcess/InputData.h"
#include "../DataProcess/OutputData.h"
#include "../NetFunction.h"
#include <functional>

namespace NeuNets {

using DataProcess::InputData;
using DataProcess::OutputData;

typedef QVector<double> row;

struct NetImage{
    QVector<row *> *rows;
};

enum neuronPos { INPUT = 0, HIDDEN, OUTPUT };

typedef double (* func)(double);
//typedef std::function <double (double)> ofunc;


struct Synaps;

class Neuron  {
public:
    Neuron();
    double summup(InputData imgs, const Func &sigmoid);
    void setSynapse(Neuron *otherNeu, double weight); //Set weight of synapse between this Neuron and otherNeu

    OutputData value;

    neuronPos getLayer() {return layer;}
    const QVector<Synaps *> &getInSyn() {return inSyn;}
    const QVector<Synaps *> &getOutSyn() {return outSyn;}

    void changeOutSyn(double *);

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

