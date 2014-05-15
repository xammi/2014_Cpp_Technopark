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
    void summup(const Func &sigmoid);
    void setSynapse(Synaps *syn);

    neuronPos getLayer() {return layer;}
    const QVector<Synaps *> &getInSyn() {return inSyn;}
    const QVector<Synaps *> &getOutSyn() {return outSyn;}

    void apply(SynapseAct action, const SynapseType type);

    void changeOutSyn(double *);
    void setVal(double sV) {if(layer == INPUT) value = sV;}
    double getVal() {if (layer == OUTPUT) return value;}
private:
    void apply(UnsafeSynapseAct action, const SynapseType type);

    double value;
    neuronPos layer;
    QVector<Synaps *> inSyn;
    QVector<Synaps *> outSyn;
};

struct Synaps {
    Synaps () {}
    Synaps (Neuron *fr, Neuron *to, double w) : weight(w), to(to), from(fr) {}

    double weight;
    Neuron *to;
    Neuron *from;
};

//================================================================
struct  NoImage: public Exception {
    QString toString() { return "Fail to get image for response"; }
};
struct  NoNeuron: public Exception {
    QString toString() { return "Fail to get neuron for set weight"; }
};
struct  FailLink: public Exception {
    QString toString() { return "No link between neurons. Can't put weight"; }
};
struct  NoWeights: public Exception {
    QString toString() { return "Can't get weight array"; }
};


}//namespace NeuNets
#endif // NEURON_H

