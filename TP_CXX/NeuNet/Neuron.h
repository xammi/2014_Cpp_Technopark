#ifndef NEURON_H
#define NEURON_H

#include "../includes.h"
#include "../PtrVector.h"
#include "../DataProcess/AbstractProcessor.h"
#include "../NetFunction.h"
#include <functional>

namespace Factory {
    class MultiLayerDestroyer;
}
//-------------------------------------------------------------------------------------------------
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

typedef function< void (Synaps *) > UnsafeSynapseAct;
typedef function< void (Synaps &) > SynapseAct;
typedef function< void (const Synaps &) > UnmodSynapseAct;
enum SynapseType { IN = 0, OUT, IN_OUT };

class Neuron {
    friend class Factory::MultiLayerDestroyer;

public:
    Neuron();
    double summup(InputData imgs, const Func &sigmoid);
    void setSynapse(Synaps *syn);

    neuronPos getLayer() {return layer;}
    const QVector<Synaps *> &getInSyn() {return inSyn;}
    const QVector<Synaps *> &getOutSyn() {return outSyn;}

    void apply(SynapseAct action, const SynapseType type);

    void changeOutSyn(double *);

private:
    void apply(UnsafeSynapseAct action, const SynapseType type);

    neuronPos layer;
    QVector<Synaps *> inSyn;
    QVector<Synaps *> outSyn;
};

struct Synaps {
    double weight;
    Neuron *to;
    Neuron *from;
    Synaps (Neuron *fr, Neuron *to, double w) : weight(w), to(to), from(fr) {}
    Synaps ();
};



}//namespace NeuNets
#endif // NEURON_H

