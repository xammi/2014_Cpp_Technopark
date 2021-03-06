#ifndef NEURON_H
#define NEURON_H

#include "../includes.h"
#include "../NetFunction.h"

namespace Factory {
    class MultiLayerDestroyer;
}
//-------------------------------------------------------------------------------------------------
namespace NeuNets {

struct Synapse;

typedef function< void (Synapse *) > UnsafeSynapseAct;
typedef function< void (Synapse &) > SynapseAct;
typedef function< void (const Synapse &) > UnmodSynapseAct;
enum SynapseType { IN = 0, OUT, IN_OUT };

class Neuron {
    friend class Factory::MultiLayerDestroyer;
public:
    Neuron();
    double summup(const Func &function);
    void setSynapse(Synapse *syn);

    const QVector<Synapse *> &getInSyn() {return inSyn;}
    const QVector<Synapse *> &getOutSyn() {return outSyn;}

    void apply(SynapseAct action, const SynapseType type);

    void changeOutSyn(double *);
    int getSynapseCnt(SynapseType) const;
    void setVal(double sV) { value = sV; }
    double getVal() const { return value; }

private:
    void apply(UnsafeSynapseAct action, const SynapseType type);

    double value;
    QVector<Synapse *> inSyn;
    QVector<Synapse *> outSyn;
};

struct Synapse {
    Synapse () {}
    Synapse (Neuron *fr, Neuron *to, double w) : weight(w), to(to), from(fr) {}
    void changeWeight(double newWeight) { weight = newWeight; }

    double weight;
    Neuron *to;
    Neuron *from;
};

typedef QVector<Neuron *> NeuVec;

typedef function< void (Neuron *) > UnsafeNeuronAct;
typedef function< void (Neuron &) > NeuronAct;
typedef function< void (const Neuron &) > UnmodNeuronAct;

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

